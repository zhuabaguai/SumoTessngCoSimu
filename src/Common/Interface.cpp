//
// Created by chenyunzhe on 2024/12/16.
//

#include "Common/Interface.h"

Interface::Interface() {
    ConfigParser::Config* config = ConfigParser::getConfig();

    std::vector<std::string> sumoGuiPaths;
    if (config->useGui){
        sumoGuiPaths = { R"(sumo-gui)" };
    }else{
        sumoGuiPaths = { R"(sumo)" };
    }
    std::string sumoCfgPath = config->sumocfg;
    std::string onceStepSecond = config->onceStepSecond;

    myGui = new GuiControl::SumoGui(sumoGuiPaths, sumoCfgPath, onceStepSecond);
    mySimulation = new SimControl::SumoSimulation();
}

Interface::~Interface() {
    delete myGui;
    delete myNet;
    delete mySimulation;

    libtraci::Simulation::close();
}

void Interface::start() {
    myGui->startSumoGui();
    myNet = new NetControl::SumoNet();
    std::vector<std::string> edgeList = myNet->getEdgeIdList();

    using Clock = std::chrono::steady_clock;
    auto lastStepTime = Clock::now();

    while (libtraci::Simulation::getMinExpectedNumber() > 0){
        auto now = Clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastStepTime).count();

        if (elapsed < 20) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20 - elapsed));
            continue;
        }

        lastStepTime = Clock::now();

        libtraci::Simulation::step();
        std::cout << "Time: " << libtraci::Simulation::getCurrentTime()  << "********************************************************************" << std::endl;

        // 1. 发送sumo的车给tessng
        auto vehicleIDsList = libtraci::Vehicle::getIDList();
        CoSimulation::VehicleList vehicleList;
        for (const auto& vehicleId : vehicleIDsList){
            if (vehicleId.compare(0, 6, "extern") == 0){
                continue;
            }

            mySimulation->paintSumoVehicle(vehicleId);
            PublicStruct::SumoVehicle* myVehicle = mySimulation->getVehicleInfo(vehicleId);

            if (myVehicle == nullptr){
                continue;
            }

            CoSimulation::VehicleProto* sumoVehicleProto = mySimulation->buildVehicleProto(myVehicle);
            vehicleList.add_vehicles()->CopyFrom(*sumoVehicleProto);
        }
        auto response = mySimulation->rpcClient->sendVehicleListAndReceiveVehicleList(vehicleList);
        int responseSize = response.vehicles_size();
        std::cout << "Received " << response.vehicles_size() << " vehicles." << std::endl;

        // 2. 接受tessng车辆并创建对应的sumo车辆
        std::unordered_set<std::string> currentExternVehicleIds;
        for (int i = 0; i < response.vehicles_size(); ++i) {
            const CoSimulation::TessngVehicleProto& vehicle = response.vehicles(i);

            std::string sumoTessngId = mySimulation->addSumoVehicle(vehicle, vehicleIDsList, edgeList);
            // 外部数据创建的车辆都带有前缀 extern_
            std::stringstream vehicleId;
            vehicleId << "extern_" << vehicle.id();
            std::string vehicleIdStr = vehicleId.str();
            mySimulation->moveSumoVehicle(vehicleIdStr, vehicle, vehicleIDsList);
            // 保存当前step收到所有外部车的车辆id
            currentExternVehicleIds.insert(vehicleIdStr);
        }

        // 3. 遍历已有集合，找出不再存在于当前 response 的 ID（要删除的）
        std::vector<std::string> idsToDelete;
        for (const auto& oldId : mySimulation->alreadyAddedExternVehicleIdSet) {
            if (currentExternVehicleIds.find(oldId) == currentExternVehicleIds.end()) {
                idsToDelete.push_back(oldId);
            }
        }

        // 4. 删除这些 ID 对应的车辆
        for (const auto& id : idsToDelete) {
            mySimulation->deleteSumoVehicle(id);
            mySimulation->alreadyAddedExternVehicleIdSet.erase(id);
        }

        // 5. 如果没收到车，就删除全部extern车
        if (!mySimulation->alreadyAddedExternVehicleIdSet.empty() && responseSize == 0){
            for (const auto& sumoExternVehicleId : mySimulation->alreadyAddedExternVehicleIdSet){
                mySimulation->deleteSumoVehicle(sumoExternVehicleId);
            }
            mySimulation->alreadyAddedExternVehicleIdSet.clear();
        }

    }
}
