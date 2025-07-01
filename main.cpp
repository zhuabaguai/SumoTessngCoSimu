#include "Common/Interface.h"

#include "RpcClient/CoSimulationClient.h"

void rpcTest(){
    std::string server_address("localhost:60051");
    CoSimulationClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    CoSimulation::Type type = CoSimulation::Type::VEHICLE;
    CoSimulation::Point3D position = client.createPoint3D(122, -129, 1.0);
    CoSimulation::Size size = client.createSize(8, 2, 1.5);
    CoSimulation::Point3D speed = client.createPoint3D(0, 0, 0);
    CoSimulation::Rotation rotation = client.createRotation(0, 0, 0);

    CoSimulation::VehicleProto testVehicle = client.createVehicleProto(-1, type, position, speed, size, rotation, "extern");
    auto response = client.sendVehicleDataAndReceiveVehicleList(testVehicle);

    std::cout << "Received " << response.vehicles_size() << " vehicles." << std::endl;

    for (int i = 0; i < response.vehicles_size(); ++i) {
        const CoSimulation::TessngVehicleProto& vehicle = response.vehicles(i);
        std::cout << vehicle.DebugString() << std::endl;
    }
}

int main() {
    rpcTest();

    Interface myInterface;
    myInterface.start();

    return 0;
}
