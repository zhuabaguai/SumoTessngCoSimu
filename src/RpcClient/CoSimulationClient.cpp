//
// Created by chenyunzhe on 2024/11/22.
//

#include "RpcClient/CoSimulationClient.h"
#include <iostream>

CoSimulationClient::CoSimulationClient(const std::shared_ptr<grpc::Channel>& channel)
        : stub_(CoSimulation::CoSimulationService::NewStub(channel)) {

}

CoSimulation::TessngVehicleList CoSimulationClient::sendVehicleDataAndReceiveVehicleList(const CoSimulation::VehicleProto& vehicle) {
    CoSimulation::TessngVehicleList response;
    grpc::ClientContext context;

    grpc::Status status = stub_->sendVehicleDataAndReceiveVehicleList(&context, vehicle, &response);

    if (status.ok()) {
    } else {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }

    return response;
}

CoSimulation::TessngVehicleList CoSimulationClient::sendVehicleListAndReceiveVehicleList(const CoSimulation::VehicleList& vehicleList) {
    CoSimulation::TessngVehicleList response;
    grpc::ClientContext context;

    grpc::Status status = stub_->sendVehicleListAndReceiveVehicleList(&context, vehicleList, &response);

    if (status.ok()) {
    } else {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }

    return response;
}

CoSimulation::Point3D CoSimulationClient::createPoint3D(double x, double y, double z){
    CoSimulation::Point3D position;
    position.set_x(x);
    position.set_y(y);
    position.set_z(z);
    return position;
}

CoSimulation::Size CoSimulationClient::createSize(double length, double width, double height){
    CoSimulation::Size size;
    size.set_length(length);
    size.set_width(width);
    size.set_height(height);
    return size;
}

CoSimulation::Rotation CoSimulationClient::createRotation(double yaw, double pitch, double roll){
    CoSimulation::Rotation rotation;
    rotation.set_yaw(yaw);
    rotation.set_pitch(pitch);
    rotation.set_roll(roll);
    return rotation;
}

CoSimulation::VehicleProto CoSimulationClient::createVehicleProto(int id, CoSimulation::Type type, const CoSimulation::Point3D &position,
                                       const CoSimulation::Point3D &linear_velocity, const CoSimulation::Size &size,
                                       const CoSimulation::Rotation &heading, const std::string &source) {

    CoSimulation::VehicleProto vehicle;

    auto now = std::chrono::system_clock::now();
    auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    vehicle.set_id(id);
    vehicle.set_type(type);
    *vehicle.mutable_position() = position;
    *vehicle.mutable_linear_velocity() = linear_velocity;
    *vehicle.mutable_size() = size;
    *vehicle.mutable_heading() = heading;
    vehicle.set_source(source);
    vehicle.set_timestamp(static_cast<double>(milliseconds_since_epoch.count()));

    return vehicle;
}

CoSimulation::VehicleList CoSimulationClient::createVehicleList(const std::vector<CoSimulation::VehicleProto> &vehicles) {
    CoSimulation::VehicleList vehicleList;

    auto now = std::chrono::system_clock::now();
    auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    vehicleList.set_timestamp(static_cast<double>(milliseconds_since_epoch.count()));

    for (const auto& vehicle : vehicles) {
        *vehicleList.add_vehicles() = vehicle;
    }

    return vehicleList;
}

