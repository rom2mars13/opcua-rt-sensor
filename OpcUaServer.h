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

    void addVariables();
    void addVariable(const char* name, int initialValue);
    // void updateLoop();

    static UA_StatusCode readCallback(UA_Server* server,
        const UA_NodeId* sessionId, void* sessionContext,
        const UA_NodeId* nodeId, void* nodeContext,
        UA_Boolean sourceTimeStamp, const UA_NumericRange* range,
        UA_DataValue* dataValue);

    static UA_StatusCode writeCallback(UA_Server* server,
        const UA_NodeId* sessionId, void* sessionContext,
        const UA_NodeId* nodeId, void* nodeContext,
        const UA_NumericRange* range, const UA_DataValue* data);

public:
    OpcUaServer();
    ~OpcUaServer();

    void run();
};

#endif // OPCUASERVER_H

