#ifndef __INCLUDE_SERVER_SERVER_H_
#define __INCLUDE_SERVER_SERVER_H_

#include "../../libs/mongoose/mongoose.h"
#include "../config/config.h"
#include "handlers.h"

typedef enum ErrCode
{
    ERR_OK = 0,
    ERR_MISSING_ENV = 1,
    ERR_INVALID_CREDENTIALS = 2,
    ERR_FILE_NOT_FOUND = 3
} EAppErrCode;

// Структура сервера
typedef struct
{
    struct mg_mgr mgr;        // Менеджер Mongoose
    serverConfig_t config;    // Конфигурация
    RequestHandler *handlers; // Динамический массив обработчиков
    size_t handlers_count;    // Количество обработчиков
    void *user_data;          // Пользовательские данные
} Server;

void logRequest(struct mg_http_message *hm);

void server_init(Server *srv, const serverConfig_t *config);
void server_register_handler(Server *srv, RequestHandler handler);
void server_start(Server *srv);
void server_stop(Server *srv);

#endif // __INCLUDE_SERVER_SERVER_H_
