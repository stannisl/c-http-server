#include "../../../include/IO/input.h"
#include "../../../include/constants.h"
#include "../../../include/server/handlers.h"

int handleNotFound(struct mg_connection *conn, struct mg_http_message *message)
{

    if (!mg_strcmp(message->method, mg_str("GET")))
        mg_http_reply(conn, HTTP_STATUS_CODE_NOT_FOUND, CONTENT_TYPE_HTML, read_file(NOT_FOUND_PAGE));

    return HTTP_STATUS_CODE_NOT_FOUND;
}
