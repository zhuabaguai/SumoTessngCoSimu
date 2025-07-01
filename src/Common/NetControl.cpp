//
// Created by chenyunzhe on 2024/12/16.
//

#include "Common/NetControl.h"

NetControl::SumoNet::SumoNet() {
    EdgeIdList = libtraci::Edge::getIDList();
}

NetControl::SumoNet::~SumoNet() = default;

std::vector<std::string> NetControl::SumoNet::getEdgeIdList() {
    return EdgeIdList;
}

