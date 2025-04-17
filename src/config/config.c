#include "../../include/config/config.h"
#include "../../include/server/server.h"
#include "../../libs/inih/ini.h"
#include "../../libs/logger/log.h"
#include <stdlib.h>
#include <string.h>

static int handler(void *user, const char *section, const char *name, const char *value)
{
    serverConfig_t *config = (serverConfig_t *)user;

    if (strcmp(section, "server") == 0)
    {
        if (strcmp(name, "port") == 0)
            config->port = atoi(value);

        else if (strcmp(name, "max_connections") == 0)
            config->max_connections = atoi(value);

        else if (strcmp(name, "timeout") == 0)
            config->timeout = atoi(value);
    }
    return 1;
}

int parseConfig(const char *filename, serverConfig_t *config)
{
    log_debug("Started parsing config %s.", filename);
    int errorCode = ini_parse(filename, handler, config);

    if (errorCode != 0)
        log_error("Failed to parse config %s. (Wrong format or file doesn't exist)", filename);

    else
        log_trace("Config parse finished successfully");

    return errorCode == 0 ? 0 : ERR_FILE_NOT_FOUND;
}
