#include "../../../include/logger/logger.h"
#include "../../../include/server/handlers.h"

/**
 * @brief Промежуточный Обработчик запросов для логирования
 * @param conn текущее соединение mg_connection
 * @param *message текущий запроc mg_http_message
 *
 * @return 0 для дальнейшей обработки.
 */
int handleLoggingRequest(struct mg_connection *conn, struct mg_http_message *message)
{
    (void)conn;
    logRequest(message);
    return 0;
}
