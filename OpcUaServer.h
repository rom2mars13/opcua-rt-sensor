#ifndef OPCUASERVER_H
#define OPCUASERVER_H

#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/accesscontrol_default.h>
#include <open62541/plugin/log_stdout.h>
#include <thread>
#include <atomic>
#include "Engine.h"

class OpcUaServer {
private:
    UA_Server* server;
    Engine engine;
    std::atomic<bool> running;
    std::thread updateThread;

    void addTemperatureVariable();
    void updateLoop();

public:
    OpcUaServer();
    ~OpcUaServer();

    void run();
};

#endif // OPCUASERVER_H
