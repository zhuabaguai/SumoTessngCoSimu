//
// Created by chenyunzhe on 2025/1/24.
//

#ifndef SUMOCOSIMUWITHTESSNG_TCPCARLACLIENT_H
#define SUMOCOSIMUWITHTESSNG_TCPCARLACLIENT_H

#define NOMINMAX

#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#pragma comment(lib, "ws2_32.lib")

class TcpCarla{
public:
    TcpCarla();
    ~TcpCarla();

    bool connectToServer(const std::string &host, uint16_t port);

    std::string getSumoJson(std::vector<std::string> sumoVehicleList);

    bool sendJson(const std::string& jsonData);

private:
    SOCKET sockfd;

};


#endif //SUMOCOSIMUWITHTESSNG_TCPCARLACLIENT_H
