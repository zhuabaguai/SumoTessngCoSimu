//
// Created by chenyunzhe on 2025/1/24.
//

#include "TcpInterface/TcpCarlaClient.h"
#include <libsumo/libtraci.h>


TcpCarla::TcpCarla() : sockfd(INVALID_SOCKET) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        exit(1);
    }
}

TcpCarla::~TcpCarla() {
    if (sockfd != INVALID_SOCKET) {
        closesocket(sockfd);
    }
    WSACleanup();
}

bool TcpCarla::connectToServer(const std::string &host, uint16_t port) {
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr{};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr);

    int result = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Connection failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Connected to server at " << host << ":" << port << std::endl;
    return true;
}

std::string TcpCarla::getSumoJson(std::vector<std::string> sumoVehicleList){
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    for (const auto& vehID : sumoVehicleList){
        libsumo::TraCIPosition position3D = libtraci::Vehicle::getPosition3D(vehID);

        rapidjson::Value object1(rapidjson::kObjectType);
        object1.AddMember("yaw", libtraci::Vehicle::getAngle(vehID), allocator);
        object1.AddMember("pitch", 0.0, allocator);
        object1.AddMember("roll", 0.0, allocator);
        object1.AddMember("speedX", 0.0, allocator);
        object1.AddMember("speedY", 0.0, allocator);
        object1.AddMember("speedZ", 0.0, allocator);
        object1.AddMember("type", 1, allocator);
        object1.AddMember("x", position3D.x, allocator);
        object1.AddMember("y", -position3D.y, allocator);
        object1.AddMember("z", position3D.z, allocator);

        rapidjson::Value key(vehID.c_str(), allocator);
        document.AddMember(key, object1, allocator);

    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    document.Accept(writer);

    return buffer.GetString();

}

bool TcpCarla::sendJson(const std::string& jsonData) {
    int result = send(sockfd, jsonData.c_str(), jsonData.length(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "JSON data sent successfully." << std::endl;
    return true;
}


