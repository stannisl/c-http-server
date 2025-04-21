#include "../../include/logger/logger.h"
#include "../../include/server/server.h"

/**
 * @brief Функция устанавливающая уроверь логирования
 */
void init_logger()
{
#ifdef DEBUG
    log_set_level(LOG_TRACE);
#else
    log_set_level(LOG_INFO);
#endif
}

/**
 * @brief Функция логирования запросов
 * @param hm указатель на http данные запроса.
 */
void logRequest(struct mg_http_message *hm)
{
    char uri[256], method[16];
    mg_snprintf(uri, sizeof(uri), "%.*s", (int)hm->uri.len, hm->uri.buf);
    mg_snprintf(method, sizeof(method), "%.*s", (int)hm->method.len, hm->method.buf);
    log_info("%s %s", method, uri);
}
