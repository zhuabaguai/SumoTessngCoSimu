//
// Created by chenyunzhe on 2024/12/12.
//

#ifndef SUMOCOSIMUWITHTESSNG_GUICONTROL_H
#define SUMOCOSIMUWITHTESSNG_GUICONTROL_H

#include <iostream>

#include <libsumo/libtraci.h>

namespace GuiControl{
    class SumoGui{
    public:
        std::vector<std::string> SumoGuiPath;
        std::string SumoCfgPath;
        std::string OnceStepSecond;

        SumoGui(std::vector<std::string> sumoGuiPath, std::string sumoCfgPath, std::string onceStepSecond);
        ~SumoGui();

        void startSumoGui() const;

    };

}

#endif //SUMOCOSIMUWITHTESSNG_GUICONTROL_H
