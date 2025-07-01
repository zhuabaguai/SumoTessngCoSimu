//
// Created by chenyunzhe on 2024/11/22.
//

#ifndef RPCCLIENT_COSIMULATIONCLIENT_H
#define RPCCLIENT_COSIMULATIONCLIENT_H

#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "CoSimulation.pb.h"
#include "CoSimulation.grpc.pb.h"


class CoSimulationClient {
public:
    explicit CoSimulationClient(const std::shared_ptr<grpc::Channel>& channel);

    CoSimulation::TessngVehicleList sendVehicleDataAndReceiveVehicleList(const CoSimulation::VehicleProto& vehicle);

    CoSimulation::TessngVehicleList sendVehicleListAndReceiveVehicleList(const CoSimulation::VehicleList& vehicleList);

    CoSimulation::Point3D createPoint3D(double x, double y, double z);

    CoSimulation::Size createSize(double length, double width, double height);

    CoSimulation::Rotation createRotation(double yaw, double pitch, double roll);

    CoSimulation::VehicleProto createVehicleProto(int id,
                                    CoSimulation::Type type,
                                    const CoSimulation::Point3D& position,
                                    const CoSimulation::Point3D& linear_velocity,
                                    const CoSimulation::Size& size,
                                    const CoSimulation::Rotation& heading,
                                    const std::string& source);

    CoSimulation::VehicleList createVehicleList(const std::vector<CoSimulation::VehicleProto>& vehicles);


private:
    std::unique_ptr<CoSimulation::CoSimulationService::Stub> stub_;
};

#endif //RPCCLIENT_COSIMULATIONCLIENT_H
