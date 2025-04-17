#include "../../../include/logger/logger.h"

int handleLoggingRequest(struct mg_connection *conn, struct mg_http_message *message)
{
    (void)conn;
    logRequest(message);
    return 0;
}
