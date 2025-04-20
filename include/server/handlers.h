#ifndef __INCLUDE_SERVER_HANDLERS_H_
#define __INCLUDE_SERVER_HANDLERS_H_

#include "../config/config.h"
#include "../types.h"

/**
 * @brief Обработчик запросов статик ресурсов
 * @param conn текущее соединение mg_connection
 * @param *message текущий запроc mg_http_message
 *
 * @return HTTP_STATUS_CODE если запрос был обработан этим обработчиком
 *            0 если запрос не был обработан.
 */
int handleStaticResource(struct mg_connection *conn, struct mg_http_message *message);

/**
 * @brief Промежуточный Обработчик запросов для логирования
 * @param conn текущее соединение mg_connection
 * @param *message текущий запроc mg_http_message
 *
 * @return 0 для дальнейшей обработки.
 */
int handleLoggingRequest(struct mg_connection *conn, struct mg_http_message *message);

/**
 * @brief Обработчик POST события по высчету рейтинга
 * @param conn текущее соединение mg_connection
 * @param *message текущий запроc mg_http_message
 *
 * @return 200 если запрос был обработан этим обработчиком
 *            0 если запрос не был обработан.
 */
int handleSubmitRating(struct mg_connection *conn, struct mg_http_message *message);

#endif // __INCLUDE_SERVER_HANDLERS_H_
