#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/accesscontrol_default.h>
#include <open62541/plugin/log_stdout.h>


int main() {
    // Create a new OPC UA server instance
    UA_Server *server = UA_Server_new();

    // Get the server's default configuration
    UA_ServerConfig *config = UA_Server_getConfig(server);

    // Apply the default configuration settings
    UA_ServerConfig_setDefault(config);

    // Clear any previous access control settings
    config->accessControl.clear(&config->accessControl);

    // Enable default access control
    // Allow anonymous access (true)
    // No specific users defined (NULL, 0)
    UA_AccessControl_default(config, true, NULL, 0, NULL);

    // Variable to control server running state
    UA_Boolean running = true;

    // Start the server; it will run while 'running' is true
    UA_StatusCode retval = UA_Server_run(server, &running);

    // Clean up and delete the server instance
    UA_Server_delete(server);

    // Return 0 if successful, otherwise 1
    return retval == UA_STATUSCODE_GOOD ? 0 : 1;
}



