//
// Created by chenyunzhe on 2024/12/16.
//

#include <chrono>
#include "Common/SimControl.h"

SimControl::SumoSimulation::SumoSimulation(){
    rpcClient = new CoSimulationClient(grpc::CreateChannel(ServerAddress, grpc::InsecureChannelCredentials()));

//    tcpClient = new TcpCarla();
//    tcpClient->connectToServer("192.168.1.99", 8999);

}

SimControl::SumoSimulation::~SumoSimulation() = default;

PublicStruct::SumoVehicle* SimControl::SumoSimulation::getVehicleInfo(const std::string &vehID) {
    auto* vehicle = new PublicStruct::SumoVehicle();

    vehicle->vehicleId = vehID;
    vehicle->speed = libtraci::Vehicle::getSpeed(vehID);
    vehicle->type = "sumo";

    vehicle->size.length = libtraci::Vehicle::getLength(vehID);
    vehicle->size.width = libtraci::Vehicle::getWidth(vehID);
    vehicle->size.height = libtraci::Vehicle::getHeight(vehID);

    PublicStruct::Rotation rotation{};
    double yaw = libtraci::Vehicle::getAngle(vehID);
    double pitch = libtraci::Vehicle::getSlope(vehID);
    rotation.yaw = yaw;
    rotation.pitch = pitch;
    rotation.roll = 0;
    vehicle->rotation = rotation;

    PublicStruct::Position myPosition{};
    libsumo::TraCIPosition position3D = libtraci::Vehicle::getPosition3D(vehID);
    myPosition.x = position3D.x;
    myPosition.y = position3D.y;
    myPosition.z = position3D.z;
    vehicle->position = myPosition;

    auto now = std::chrono::system_clock::now();
    auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch());
    auto timestamp_in_seconds = static_cast<double>(seconds_since_epoch.count());
    vehicle->timestamp = timestamp_in_seconds;

    return vehicle;
}

void SimControl::SumoSimulation::paintSumoVehicle(const std::string &vehID){
    if (vehID.compare(0, 6, "extern") == 0){
        return;
    }
    libtraci::Vehicle::setColor(vehID, libsumo::TraCIColor(0, 255, 255));
}

std::string SimControl::SumoSimulation::addSumoVehicle(const CoSimulation::TessngVehicleProto& externVehicle, const std::vector<std::string>& vehicleIdList, const std::vector<std::string>& edgeIdList){
    std::stringstream vehicleId;
    vehicleId << "extern_" << externVehicle.id();
    std::string vehicleIdStr = vehicleId.str();

    // 如果包含这个对象，则直接pass
    if (alreadyAddedExternVehicleIdSet.contains(vehicleIdStr)){
        std::cout << "exist pass " << vehicleIdStr << std::endl;
        return "";
    }

    std::vector<std::string> myRouteEdgeList {edgeIdList.at(0)};
    libtraci::Vehicle::add(vehicleIdStr, "");

    // 创建成功插入集合
    if (!alreadyAddedExternVehicleIdSet.contains(vehicleIdStr)){
        alreadyAddedExternVehicleIdSet.insert(vehicleIdStr);
        std::cout << "add success! " << vehicleIdStr << std::endl;
    }

    return vehicleIdStr;
}

void SimControl::SumoSimulation::moveSumoVehicle(const std::string &vehID, const CoSimulation::TessngVehicleProto& externVehicle, const std::vector<std::string>& vehicleIdList){
    std::stringstream vehicleId;
    vehicleId << "extern_" << externVehicle.id();
    std::string vehicleIdStr = vehicleId.str();

    // 如果这个车不是我创建的，直接pass
    if (!alreadyAddedExternVehicleIdSet.contains(vehicleIdStr)){
        return;
    }

    // 如果这个车已经被sumo系统移除，则同步移除alreadyAddedExternVehicleIdSet中的id
    if (!(std::find(vehicleIdList.begin(), vehicleIdList.end(), vehicleIdStr) != vehicleIdList.end())){
        return;
    }

    // 设置颜色和速度
    libtraci::Vehicle::moveToXY(vehicleIdStr, "", -1, externVehicle.position().x(), externVehicle.position().y(), externVehicle.heading().yaw(), 2);
    libtraci::Vehicle::setSpeed(vehicleIdStr, 0);
    libtraci::Vehicle::setSpeedMode(vehicleIdStr, 0);
    libtraci::Vehicle::setRoutingMode(vehicleIdStr, 0);

    // 设置颜色和尺寸
    libtraci::Vehicle::setColor(vehicleIdStr, libsumo::TraCIColor(255, 0, 0));
    libtraci::Vehicle::setLength(vehicleIdStr, 5);
    libtraci::Vehicle::setWidth(vehicleIdStr, 2);
}

void SimControl::SumoSimulation::deleteSumoVehicle(const std::string &vehId) {
    libtraci::Vehicle::remove(vehId);
}

CoSimulation::VehicleProto* SimControl::SumoSimulation::buildVehicleProto(PublicStruct::SumoVehicle *sumoVehicle){
    // 如果这个车辆对象没有被记录，进行自定义Id登记
    if (!SumoStringId2CustomIdMap.contains(sumoVehicle->vehicleId)){
        SumoStringId2CustomIdMap[sumoVehicle->vehicleId] = initVehicleId;
        CustomIdMap2SumoStringId[initVehicleId] = sumoVehicle->vehicleId;
        // 每次登记后自加
        initVehicleId ++;
    }

    // 求分解速度
    double headingRad = sumoVehicle->rotation.yaw * M_PI / 180.0;
    double vx = sumoVehicle->speed * sin(headingRad);
    double vy = sumoVehicle->speed * cos(headingRad);

    // 重新组proto包
    auto* vehicle = new CoSimulation::VehicleProto;

    auto now = std::chrono::system_clock::now();
    auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    vehicle->set_id(SumoStringId2CustomIdMap[sumoVehicle->vehicleId]);

    vehicle->set_type(CoSimulation::Type::VEHICLE);

    vehicle->set_source(sumoVehicle->type);

    vehicle->mutable_position()->set_x(sumoVehicle->position.x);
    vehicle->mutable_position()->set_y(-sumoVehicle->position.y) ;
    vehicle->mutable_position()->set_z(sumoVehicle->position.z);

    vehicle->mutable_linear_velocity()->set_x(vx);
    vehicle->mutable_linear_velocity()->set_y(vy);
    vehicle->mutable_linear_velocity()->set_z(0);

    vehicle->mutable_size()->set_length(sumoVehicle->size.length);
    vehicle->mutable_size()->set_width(sumoVehicle->size.width);
    vehicle->mutable_size()->set_height(sumoVehicle->size.height);

    vehicle->mutable_heading()->set_yaw(sumoVehicle->rotation.yaw);
    vehicle->mutable_heading()->set_pitch(sumoVehicle->rotation.pitch);
    vehicle->mutable_heading()->set_roll(sumoVehicle->rotation.roll);

    vehicle->set_timestamp(static_cast<double>(milliseconds_since_epoch.count()));

    return vehicle;
}
