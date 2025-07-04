#include "OpcUaServer.h"
#include "Engine.h"

#include <thread>
#include <atomic>
#include <chrono>


void OpcUaServer::addTemperatureVariable() {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, (char*)"Temperature");
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 initialTemp = engine.getTemperature();
    UA_Variant_setScalar(&attr.value, &initialTemp, &UA_TYPES[UA_TYPES_INT32]);
    attr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"Temperature");

    UA_Server_addVariableNode(server, currentNodeId,
                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                             UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                             UA_QUALIFIEDNAME(1, (char*)"Temperature"),
                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                             attr, nullptr, nullptr);
}

void OpcUaServer::updateLoop() {
    while (running) {
        int temp = engine.getTemperature();
        UA_Variant value;
        UA_Variant_setScalar(&value, &temp, &UA_TYPES[UA_TYPES_INT32]);
        UA_Server_writeValue(server, UA_NODEID_STRING(1, (char*)"Temperature"), value);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

OpcUaServer::OpcUaServer() {
    running = true;

    server = UA_Server_new();
    UA_ServerConfig* config = UA_Server_getConfig(server);
    UA_ServerConfig_setDefault(config);

    config->accessControl.clear(&config->accessControl);
    UA_AccessControl_default(config, true, nullptr, 0, nullptr);

    addTemperatureVariable();

    updateThread = std::thread(&OpcUaServer::updateLoop, this);
}

OpcUaServer::~OpcUaServer() {
    running = false;
    if (updateThread.joinable())
        updateThread.join();

    UA_Server_delete(server);
}

void OpcUaServer::run() {
    UA_Boolean serverRunning = true;
    UA_Server_run(server, &serverRunning);
}



