## 项目介绍
本项目旨在分享**开源交通仿真软件 SUMO 的 C++ 二次开发实践经验**，填补当前中文互联网中关于 SUMO C++ 开发资料的空白。项目中整理了完整的开发编译流程、关键接口说明以及实际应用示例，帮助开发者快速上手并灵活拓展 SUMO 的功能。

同时，也诚挚推荐国产优秀的交通仿真平台 **TESS NG**，希望通过项目推广推动国产仿真技术的发展与应用！

![红色车辆为TESS NG车辆，蓝色车辆为SUMO车辆](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751273591836-bf0d6578-1926-4377-8b15-36db4a0d8e03.png)

## 项目功能
+ **支持将 Python TraCI 脚本迁移为 C++ 的 libtraci 实现，显著提升运行效率，满足科研与工程对性能的更高要求。**
+ **支持动态创建与管理车辆对象，适用于交通管理与交通控制相关科研场景。**
+ **支持多类型交通流混合干扰建模，便于对国产交通仿真软件功能是否可替代 SUMO 进行深入对比研究。**

## 文件目录说明
```

SumoCoSimuWithTessng

├── /include						->项目头文件

├── /lib							->项目三方静态库

├── /src							->项目源文件

├── /SumoDependence				->sumo cpp开发依赖（动态库、头文件、静态库）

│  ├── /bin/						->可执行文件依赖的dll动态库

│  │  ├── libtracicpp.dll

│  │  ├── ...

│  │  ├── xxx.dll

│  ├── /include/					->项目依赖的相关头文件

│  │  ├── /libsumo/

│  │  │  ├── Simulation.h

│  │  │  ├── ...

│  │  │  ├── xxx.h

│  ├── /lib/						->编译时所需的lib静态库

│  │  ├── libsumocpp.lib

│  │  ├── libtracicpp.lib

├── /TESSNG.zip					->TESSNG可执行文件zip压缩包

├── /maps						->sumo仿真路网文件

│  ├── /Crossing8/

│  │  ├── Crossing8Course.net.xml

│  │  ├── Crossing8Course.sumocfg

│  │  ├── Crossing8Course.xodr

│  │  └── routes.rou.xml

├── CMakeLists.txt					-> CMake文件

├── config.json					->项目运行配置文件

├── main.cpp						->主程序

├── README.md					->README

├── LICENSE.txt					->开源证书

```

## 开发指南
项目基于Windows平台开发，且只支持release模式。需要安装visual studio以及cmake。

- [visual studio]（微软集成开发环境）

[https://learn.microsoft.com/zh-cn/cpp/build/vscpp-step-0-installation?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/build/vscpp-step-0-installation?view=msvc-170)

- [cmake]（开源跨平台自动构建系统）

[https://blog.csdn.net/zhouzhiwengang/article/details/133430457](https://blog.csdn.net/zhouzhiwengang/article/details/133430457)

## 使用到的框架
- [grpc - 谷歌开源rpc通信库] ([https://github.com/grpc/grpc](https://github.com/grpc/grpc))

- [TESS NG - 济达交通国产交通微观仿真软件] ([https://www.jidatraffic.com/#/home](https://www.jidatraffic.com/#/home))

## 项目编译
1、下载代码后，文件夹内新建build文件夹。

![项目代码文件夹](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269169948-937dd6e9-785c-46cc-b28c-bed93b6b094a.png)

2、cmake-gui打开文件夹。CMAKE_INSTALL_PREFIX的Value填写为第一步创建的build文件夹绝对路径（作者的build文件夹绝对路径为 "F:\Projects\Sumo\Sumo\build"）。点击左下角的Configure按钮，等待提示框中出现Configuring done。

![cmake配置](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269218619-9b3c61b8-85fe-49fa-aa53-fe4cff027942.png)

3、Configuring done后点击Generate按钮，等待提示框中出现Generating done。

![cmake生成visual studio解决方案](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269447655-fddec449-fc91-42c5-ac8f-f71b40febd84.png)

4、双击新建的build文件夹，再双击SumoCoSimuWithTessng.sln打开visual studio解决方案。

![由cmake生成的visual studio解决方案](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269628401-6281515b-c99e-4106-ab0c-2525168d5361.png)

5、双击sln文件，打开visual studio项目。

![visual studio项目](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269692153-0e97d4b8-bccb-4dda-b8e5-3fb414a01c7b.png)

6、右键ALL_BUILD点击生成，开始编译项目。

![使用visual studio编译项目](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269742885-f7e5bae2-5c56-4636-8957-97a9002c93dc.png)

7、生成完毕后，visual studio会在build文件夹下生成Release文件夹，Release文件夹下的SumoCoSimuWithT essng.exe为编译后的可执行文件。参考《文件目录说明》，将SumoCoSimuWithTessng/SumoDependence/ bin下的dll文件；SumoCoSimuWithTessng/maps文件夹；SumoCoSimuWithTessng/config.json全部拷贝到build/Release目录下。

![项目可执行文件](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751269838879-aca94006-42cd-489c-ac90-124d29168c95.png)

8、运行可执行文件。会打开config.json中配置的默认路网Crossing8Course.sumocfg.

![双击运行](https://cdn.nlark.com/yuque/0/2025/png/40730850/1751270481752-ca3d5647-3b3a-4cf4-a0c4-bc4cac03762f.png)

## SUMO libtraci相关代码
项目中用到libtraci相关接口的部分代码。

1、SimControl.cpp

```cpp
void SimControl::SumoSimulation::paintSumoVehicle(const std::string &vehID){
    if (vehID.compare(0, 6, "extern") == 0){
        return;
    }
    libtraci::Vehicle::setColor(vehID, libsumo::TraCIColor(0, 255, 255));
}
```

```cpp
std::string SimControl::SumoSimulation::addSumoVehicle(const CoSimulation::TessngVehicleProto& externVehicle, const std::vector<std::string>& vehicleIdList, const std::vector<std::string>& edgeIdList){
    std::stringstream vehicleId;
    vehicleId << "extern_" << externVehicle.id();
    std::string vehicleIdStr = vehicleId.str();

    // 如果包含这个对象，则直接pass
    if (alreadyAddedExternVehicleIdSet.contains(vehicleIdStr)){
        std::cout << "exist pass " << vehicleIdStr << std::endl;
        return "";
    }

    std::vector<std::string> myRouteEdgeList {edgeIdList.at(0)};
    libtraci::Vehicle::add(vehicleIdStr, "");

    // 创建成功插入集合
    if (!alreadyAddedExternVehicleIdSet.contains(vehicleIdStr)){
        alreadyAddedExternVehicleIdSet.insert(vehicleIdStr);
        std::cout << "add success! " << vehicleIdStr << std::endl;
    }

    return vehicleIdStr;
}
```

```cpp
void SimControl::SumoSimulation::moveSumoVehicle(const std::string &vehID, const CoSimulation::TessngVehicleProto& externVehicle, const std::vector<std::string>& vehicleIdList){
    std::stringstream vehicleId;
    vehicleId << "extern_" << externVehicle.id();
    std::string vehicleIdStr = vehicleId.str();

    // 如果这个车不是我创建的，直接pass
    if (!alreadyAddedExternVehicleIdSet.contains(vehicleIdStr)){
        return;
    }

    // 如果这个车已经被sumo系统移除，则同步移除alreadyAddedExternVehicleIdSet中的id
    if (!(std::find(vehicleIdList.begin(), vehicleIdList.end(), vehicleIdStr) != vehicleIdList.end())){
        return;
    }

    // 设置颜色和速度
    libtraci::Vehicle::moveToXY(vehicleIdStr, "", -1, externVehicle.position().x(), externVehicle.position().y(), externVehicle.heading().yaw(), 2);
    libtraci::Vehicle::setSpeed(vehicleIdStr, 0);
    libtraci::Vehicle::setSpeedMode(vehicleIdStr, 0);
    libtraci::Vehicle::setRoutingMode(vehicleIdStr, 0);

    // 设置颜色和尺寸
    libtraci::Vehicle::setColor(vehicleIdStr, libsumo::TraCIColor(255, 0, 0));
    libtraci::Vehicle::setLength(vehicleIdStr, 5);
    libtraci::Vehicle::setWidth(vehicleIdStr, 2);
}
```

```cpp
PublicStruct::SumoVehicle* SimControl::SumoSimulation::getVehicleInfo(const std::string &vehID) {
    auto* vehicle = new PublicStruct::SumoVehicle();

    vehicle->vehicleId = vehID;
    vehicle->speed = libtraci::Vehicle::getSpeed(vehID);
    vehicle->type = "sumo";

    vehicle->size.length = libtraci::Vehicle::getLength(vehID);
    vehicle->size.width = libtraci::Vehicle::getWidth(vehID);
    vehicle->size.height = libtraci::Vehicle::getHeight(vehID);

    PublicStruct::Rotation rotation{};
    double yaw = libtraci::Vehicle::getAngle(vehID);
    double pitch = libtraci::Vehicle::getSlope(vehID);
    rotation.yaw = yaw;
    rotation.pitch = pitch;
    rotation.roll = 0;
    vehicle->rotation = rotation;

    PublicStruct::Position myPosition{};
    libsumo::TraCIPosition position3D = libtraci::Vehicle::getPosition3D(vehID);
    myPosition.x = position3D.x;
    myPosition.y = position3D.y;
    myPosition.z = position3D.z;
    vehicle->position = myPosition;

    auto now = std::chrono::system_clock::now();
    auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch());
    auto timestamp_in_seconds = static_cast<double>(seconds_since_epoch.count());
    vehicle->timestamp = timestamp_in_seconds;

    return vehicle;
}
```

2、GuiControl.cpp

```cpp
void GuiControl::SumoGui::startSumoGui() const {
    if (SumoGuiPath.empty() || SumoCfgPath.empty()){
        return;
    }
    // 指定50001端口
    try{
        libtraci::Simulation::start({SumoGuiPath[0], "-c", SumoCfgPath, "--step-length", OnceStepSecond}, 50001);

    }catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}
```

## 作者
邮箱：cyz.sh@foxmail.com

github：[https://github.com/zhuabaguai](https://github.com/zhuabaguai)

## 版权说明
该项目签署了MIT 授权许可，详情请参阅 [LICENSE.txt]

