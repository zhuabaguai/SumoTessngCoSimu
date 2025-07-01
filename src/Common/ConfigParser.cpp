//
// Created by chenyunzhe on 2024/12/16.
//

#include "Common/ConfigParser.h"

ConfigParser::ConfigParser() = default;

ConfigParser::~ConfigParser() = default;

ConfigParser::Config *ConfigParser::getConfig() {
    auto* myConfig = new ConfigParser::Config();

    FILE* fp = fopen("../config.json", "r");
    if (!fp) {
        std::cerr << "Could not open file!" << std::endl;
    }

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    rapidjson::Document document;
    document.ParseStream(is);

    if (document.HasParseError()) {
        std::cerr << "Error parsing JSON" << std::endl;
        fclose(fp);
    }

    if (document.HasMember("use_gui") && document["use_gui"].IsBool()) {
        bool use_gui = document["use_gui"].GetBool();
        std::cout << "use_gui: " << use_gui << std::endl;
        myConfig->useGui = use_gui;
    }

    if (document.HasMember("sumo_cfg_path") && document["sumo_cfg_path"].IsString()) {
        std::string sumoCfgPath = document["sumo_cfg_path"].GetString();
        std::cout << "sumo_cfg_path: " << sumoCfgPath << std::endl;
        myConfig->sumocfg = sumoCfgPath;
    }

    if (document.HasMember("one_step_second") && document["one_step_second"].IsString()) {
        std::string oneStepSecond = document["one_step_second"].GetString();
        std::cout << "one_step_second: " << oneStepSecond << std::endl;
        myConfig->onceStepSecond = oneStepSecond;
    }

    fclose(fp);

    return myConfig;
}

