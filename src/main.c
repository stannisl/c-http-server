#include "../include/config/config.h"
#include "../include/logger/logger.h"
#include "../include/server/handlers.h"
#include "../include/server/server.h"

int main(void)
{
    init_logger();

    EAppErrCode errCode;
    serverConfig_t config;
    Server server;

    errCode = parseConfig("./server_config.ini", &config);

    if (errCode == ERR_OK)
    {
        server_init(&server, &config);

        server_register_handler(&server, handleLoggingRequest);
        server_register_handler(&server, handleStaticResource);
        server_register_handler(&server, handleSubmitRating);

        server_start(&server);
        server_stop(&server);
    }

    return 0;
}
