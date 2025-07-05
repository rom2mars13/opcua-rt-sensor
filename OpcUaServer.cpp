#include "OpcUaServer.h"
#include <open62541/server_config_default.h>
#include <chrono>

// Read callback
UA_StatusCode OpcUaServer::readCallback(UA_Server* server,
    const UA_NodeId* sessionId, void* sessionContext,
    const UA_NodeId* nodeId, void* nodeContext,
    UA_Boolean sourceTimeStamp, const UA_NumericRange* range,
    UA_DataValue* dataValue) {

    OpcUaServer* self = static_cast<OpcUaServer*>(nodeContext);
    if (!self) return UA_STATUSCODE_BADINTERNALERROR;

    if (!self) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "nodeContext is null");
        return UA_STATUSCODE_BADINTERNALERROR;
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "reading temperature");


    int temp = self->engine.getTemperature();

    UA_Variant_setScalarCopy(&dataValue->value, &temp, &UA_TYPES[UA_TYPES_INT32]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

// Write callback
UA_StatusCode OpcUaServer::writeCallback(UA_Server* server,
    const UA_NodeId* sessionId, void* sessionContext,
    const UA_NodeId* nodeId, void* nodeContext,
    const UA_NumericRange* range, const UA_DataValue* data) {

    OpcUaServer* self = static_cast<OpcUaServer*>(nodeContext);
    if (!self) return UA_STATUSCODE_BADINTERNALERROR;

    if (UA_Variant_hasScalarType(&data->value, &UA_TYPES[UA_TYPES_INT32])) {
        int newTemp = *(int*)data->value.data;
        self->engine.setTemperature(newTemp);
        return UA_STATUSCODE_GOOD;
    }
    return UA_STATUSCODE_BADTYPEMISMATCH;
}

void OpcUaServer::addVariable(const char* name, int initialValue) {
    UA_NodeId nodeId = UA_NODEID_STRING(1, (char*)name);

    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Variant_setScalar(&attr.value, &initialValue, &UA_TYPES[UA_TYPES_INT32]);
    attr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)name);

    UA_Server_addVariableNode(server, nodeId,
                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                             UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                             UA_QUALIFIEDNAME(1, (char*)name),
                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                             attr, nullptr, nullptr);

    UA_DataSource ds;
    ds.read = readCallback;
    ds.write = writeCallback;

    UA_Server_setVariableNode_dataSource(server, nodeId, ds);

    // Important : associe le contexte à ce nœud pour l’utiliser dans les callbacks
    UA_Server_setNodeContext(server, nodeId, this);
}



OpcUaServer::OpcUaServer() : running(true) {
    server = UA_Server_new();
    UA_ServerConfig* config = UA_Server_getConfig(server);
    UA_ServerConfig_setDefault(config);

    addVariable("Temperature", engine.getTemperature());
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
