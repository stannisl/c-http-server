#ifndef __INCLUDE_CONFIG_CONFIG_H
#define __INCLUDE_CONFIG_CONFIG_H

typedef struct
{
    int port;
    int max_connections;
    int timeout;
    // char log_file[256];
} serverConfig_t;

int parseConfig(const char *filename, serverConfig_t *serverConfig);

#endif // __INCLUDE_CONFIG_CONFIG_H
