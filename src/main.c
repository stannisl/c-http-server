#include "../include/config/config.h"
#include "../include/server/server.h"
#include "../include/logger/logger.h"

int main(void)
{
    // init_logger();
    log_set_level(LOG_TRACE);
    struct mg_mgr mgr;
    EAppErrCode errCode;
    serverConfig_t config;

    errCode = parseConfig("./server_config.ini", &config);
    if (errCode == ERR_OK) {
        startServer(&mgr, &config);
    }
    // mg_mgr_free(&mgr);

    return 0;
}
