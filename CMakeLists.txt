cmake_minimum_required(VERSION 3.10)
project(opcua_rt_sensor)

set(CMAKE_CXX_STANDARD 17)

add_executable(server 
    main.cpp 
    OpcUaServer.cpp 
    Engine.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include)

target_link_libraries(server PRIVATE
    /usr/local/lib/libopen62541.a
    pthread
    mbedtls
    mbedx509
    mbedcrypto
)

