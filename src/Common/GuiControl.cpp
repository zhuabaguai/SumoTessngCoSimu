//
// Created by chenyunzhe on 2024/12/12.
//

#include <utility>

#include "Common/GuiControl.h"

GuiControl::SumoGui::SumoGui(std::vector<std::string> sumoGuiPath, std::string sumoCfgPath, std::string onceStepSecond)
        : SumoGuiPath(std::move(sumoGuiPath)), SumoCfgPath(std::move(sumoCfgPath)), OnceStepSecond(std::move(onceStepSecond)){
    std::cout << "Start sumo simulation." << std::endl;
}

void GuiControl::SumoGui::startSumoGui() const {
    if (SumoGuiPath.empty() || SumoCfgPath.empty()){
        return;
    }

    try{
        libtraci::Simulation::start({SumoGuiPath[0], "-c", SumoCfgPath, "--step-length", OnceStepSecond}, 50001);

    }catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

GuiControl::SumoGui::~SumoGui() = default;
