#ifndef __INCLUDE_TYPES_H__
#define __INCLUDE_TYPES_H__

#include "../libs/inih/ini.h"
#include "../libs/logger/log.h"
#include "../libs/mongoose/mongoose.h"
#include <stdio.h>
#include <stdlib.h>

typedef int (*RequestHandler)(struct mg_connection *conn, struct mg_http_message *message);

typedef enum ErrCode
{
    ERR_OK = 0,
    ERR_MISSING_ENV = 1,
    ERR_INVALID_CREDENTIALS = 2,
    ERR_FILE_NOT_FOUND = 3
} EAppErrCode;

typedef struct
{
    int port;
    int max_connections;
    int timeout;
    // char log_file[256];
} serverConfig_t;

typedef struct
{
    struct mg_mgr mgr;        // Менеджер Mongoose
    serverConfig_t config;    // Конфигурация
    RequestHandler *handlers; // Динамический массив обработчиков
    size_t handlers_count;    // Количество обработчиков
    void *user_data;          // Пользовательские данные
} Server;

#endif // __INCLUDE_TYPES_H__
