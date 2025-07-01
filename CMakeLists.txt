cmake_minimum_required(VERSION 3.23)
project(SumoCoSimuWithTessng)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

set(CMAKE_CXX_STANDARD 20)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# vcpkg libs
set(THIRD_PARTY_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# set Sumo include
set(SUMO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SumoDependence/include")

# set Sumo lib
set(SUMO_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SumoDependence/lib")

# set ThirdParty include
set(THIRDPARTY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty")

include_directories(
        ${SUMO_INCLUDE_DIR}
        ${SUMO_INCLUDE_DIR}/libsumo

        ${CMAKE_CURRENT_SOURCE_DIR}/include

        # rapidjson
        ${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson

        # rpc
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RpcClient

        # thirdparty .h dir
        ${THIRDPARTY_INCLUDE_DIR}
        ${THIRDPARTY_INCLUDE_DIR}/protobuf
        ${THIRDPARTY_INCLUDE_DIR}/grpc
        ${THIRDPARTY_INCLUDE_DIR}/grpc++
        ${THIRDPARTY_INCLUDE_DIR}/absl
        ${THIRDPARTY_INCLUDE_DIR}/openssl
        ${THIRDPARTY_INCLUDE_DIR}/re2
        ${THIRDPARTY_INCLUDE_DIR}/upb
)

link_directories(
        ${SUMO_LIB_DIR}

        ${THIRD_PARTY_LIB_PATH}
)

# set .h
set(HEADERS
        # Common Methods
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Common/GuiControl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Common/SimControl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Common/NetControl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Common/CommonStructs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Common/Interface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Common/ConfigParser.h
        # Rpc Client
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RpcClient/CoSimulationClient.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RpcClient/CoSimulation.grpc.pb.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RpcClient/CoSimulation.pb.h
        # Tcp Carla
        ${CMAKE_CURRENT_SOURCE_DIR}/include/TcpInterface/TcpCarlaClient.h
)

# set .cpp
set(SOURCE
        # Common Methods
        main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/GuiControl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/SimControl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/NetControl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/Interface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Common/ConfigParser.cpp
        # Rpc Client
        ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcClient/CoSimulationClient.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcClient/CoSimulation.grpc.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/RpcClient/CoSimulation.pb.cc
        # Tcp Carla
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TcpInterface/TcpCarlaClient.cpp)

add_executable(SumoCoSimuWithTessng ${SOURCE} ${HEADERS})

target_link_libraries(SumoCoSimuWithTessng
        libsumocpp
        libtracicpp

        abseil_dll
        absl_decode_rust_punycode
        absl_demangle_rust
        absl_flags_commandlineflag
        absl_flags_commandlineflag_internal
        absl_flags_config
        absl_flags_internal
        absl_flags_marshalling
        absl_flags_parse
        absl_flags_private_handle_accessor
        absl_flags_program_name
        absl_flags_reflection
        absl_flags_usage
        absl_flags_usage_internal
        absl_log_flags
        absl_poison
        absl_utf8_for_code_point
        address_sorting
        cares
        gpr
        grpc
        grpc_authorization_provider
        grpc_plugin_support
        grpc_unsecure
        grpc++
        grpc++_alts
        grpc++_error_details
        grpc++_reflection
        grpc++_unsecure
        grpcpp_channelz
        libcrypto
        libprotobuf
        libprotobuf-lite
        libprotoc
        libssl
        re2
        upb
        utf8_range
        utf8_validity
        zlib
)
