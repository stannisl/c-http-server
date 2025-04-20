#include "../../../include/IO/input.h"
#include "../../../include/constants.h"
#include "../../../include/server/handlers.h"
#include "../../../include/server/server.h"

/**
 * @brief Обработчик запросов статик ресурсов
 * @param conn текущее соединение mg_connection
 * @param *message текущий запроc mg_http_message
 *
 * @return HTTP_STATUS_CODE если запрос был обработан этим обработчиком
 *            0 если запрос не был обработан.
 */
int handleStaticResource(struct mg_connection *conn, struct mg_http_message *message)
{
    int code = 0;

    if (!mg_strcmp(message->uri, mg_str("/")) && !mg_strcmp(message->method, mg_str("GET")))
    {
        char *data = read_file(SATISFACTION_FORM_HTML);
        mg_http_reply(conn, HTTP_STATUS_CODE_OK, CONTENT_TYPE_HTML, data);
        free(data);
        code = HTTP_STATUS_CODE_OK;
    }
    else if (!mg_strcmp(message->uri, mg_str("/styles.css")))
    {
        char *data = read_file(STYLES_CSS);
        mg_http_reply(conn, HTTP_STATUS_CODE_OK, CONTENT_TYPE_CSS, data);
        free(data);
        code = HTTP_STATUS_CODE_OK;
    }

    return code;
}
