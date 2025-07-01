//
// Created by chenyunzhe on 2024/12/16.
//

#ifndef SUMOCOSIMUWITHTESSNG_SIMCONTROL_H
#define SUMOCOSIMUWITHTESSNG_SIMCONTROL_H

#include <iostream>
#include <cmath>
#include <utility>
#include <unordered_set>
#include <sstream>
#include <string>

#include <libsumo/libtraci.h>

#include "CommonStructs.h"
#include "RpcClient/CoSimulationClient.h"
#include "TcpInterface/TcpCarlaClient.h"
#include "RpcClient/CoSimulation.pb.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace SimControl {
    class SumoSimulation {
    public:
        SumoSimulation();

        ~SumoSimulation();

        // Tcp Client prt
        TcpCarla* tcpClient;

        // Rpc Client ptr
        std::string ServerAddress = "localhost:60051";
        CoSimulationClient* rpcClient;

        // already created extern vehicles in sumo
        std::unordered_set<std::string> alreadyAddedExternVehicleIdSet;

        // get sumo vehicle info
        PublicStruct::SumoVehicle *getVehicleInfo(const std::string &vehID);

        // repaint sumo vehicle
        void paintSumoVehicle(const std::string &vehID);

        // add sumo vehicle
        std::string addSumoVehicle(const CoSimulation::TessngVehicleProto& externVehicle, const std::vector<std::string>& vehicleIdList, const std::vector<std::string>& edgeIdList);

        // move sumo vehicle
        void moveSumoVehicle(const std::string &vehID, const CoSimulation::TessngVehicleProto& externVehicle, const std::vector<std::string>& vehicleIdList);

        // delete sumo vehicle
        void deleteSumoVehicle(const std::string &vehId);

        // build vehicle proto
        CoSimulation::VehicleProto* buildVehicleProto(PublicStruct::SumoVehicle *sumoVehicle);

    private:
        // offset
        std::vector<int> offset {0, 0};

        // sumo vehicle id init
        long initVehicleId = 1000;
        std::map<std::string, long> SumoStringId2CustomIdMap;
        std::map<long, std::string> CustomIdMap2SumoStringId;

    };
}

#endif //SUMOCOSIMUWITHTESSNG_SIMCONTROL_H