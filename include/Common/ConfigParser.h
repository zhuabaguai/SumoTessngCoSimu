//
// Created by chenyunzhe on 2024/12/16.
//

#ifndef SUMOCOSIMUWITHTESSNG_CONFIGPARSER_H
#define SUMOCOSIMUWITHTESSNG_CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

class ConfigParser{
public:
    ConfigParser();
    ~ConfigParser();

    struct Config{
        bool useGui;
        std::string sumocfg;
        std::string onceStepSecond;
    };

    static Config* getConfig();

};


#endif //SUMOCOSIMUWITHTESSNG_CONFIGPARSER_H
