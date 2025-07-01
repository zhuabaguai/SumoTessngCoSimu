//
// Created by chenyunzhe on 2024/12/16.
//

#ifndef SUMOCOSIMUWITHTESSNG_COMMONSTRUCTS_H
#define SUMOCOSIMUWITHTESSNG_COMMONSTRUCTS_H

#include <iostream>

namespace PublicStruct{
    struct Rotation{
        double yaw = 0.0;
        double pitch = 0.0;
        double roll = 0.0;
    };

    struct Position{
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    struct Size{
        double length = 0.0;
        double width = 0.0;
        double height = 0.0;
    };

    struct SumoVehicle{
        std::string vehicleId = "sumo";
        double speed = 0.0;
        Rotation rotation;
        Position position;
        Size size;
        std::string type = "sumo";
        double timestamp = 0.0;
    };

    struct ExternVehicle{
        std::string vehicleId = "extern";
        double speed = 0.0;
        Rotation rotation;
        Position position;
        std::string type = "extern";
        std::string source = "tessng";
        double timestamp = 0.0;
    };

}

#endif //SUMOCOSIMUWITHTESSNG_COMMONSTRUCTS_H
