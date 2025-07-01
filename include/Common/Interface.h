//
// Created by chenyunzhe on 2024/12/16.
//

#ifndef SUMOCOSIMUWITHTESSNG_INTERFACE_H
#define SUMOCOSIMUWITHTESSNG_INTERFACE_H

#include <thread>
#include <chrono>

#include "GuiControl.h"
#include "SimControl.h"
#include "NetControl.h"
#include "ConfigParser.h"

class Interface{
public:
    GuiControl::SumoGui* myGui;
    SimControl::SumoSimulation* mySimulation;
    NetControl::SumoNet* myNet{};

    Interface();
    ~Interface();

    void start();

    bool once = false;

};

#endif //SUMOCOSIMUWITHTESSNG_INTERFACE_H
