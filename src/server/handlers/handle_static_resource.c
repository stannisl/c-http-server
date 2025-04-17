#include "../../../include/IO/input.h"
#include "../../../include/constants.h"
#include "../../../include/server/handlers.h"
#include "../../../include/server/server.h"

int handleStaticResource(struct mg_connection *conn, struct mg_http_message *message)
{
    int code = 0;

    if (!mg_strcmp(message->uri, mg_str("/")) && !mg_strcmp(message->method, mg_str("GET")))
    {
        mg_http_reply(conn, HTTP_STATUS_CODE_OK, CONTENT_TYPE_HTML, read_file(SATISFACTION_FORM_HTML));
        code = HTTP_STATUS_CODE_OK;
    }
    else if (!mg_strcmp(message->uri, mg_str("/styles.css")))
    {
        mg_http_reply(conn, HTTP_STATUS_CODE_OK, CONTENT_TYPE_CSS, read_file(STYLES_CSS));
        code = HTTP_STATUS_CODE_OK;
    }

    return code;
}
