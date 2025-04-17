#include "../../include/logger/logger.h"

#include "../../include/server/server.h"

void init_logger()
{
#ifdef DEBUG
    log_set_level(LOG_TRACE);
#else
    log_set_level(LOG_WARN);
#endif
}

void logRequest(struct mg_http_message *hm)
{
    char uri[256], method[16];
    mg_snprintf(uri, sizeof(uri), "%.*s", (int)hm->uri.len, hm->uri.buf);
    mg_snprintf(method, sizeof(method), "%.*s", (int)hm->method.len, hm->method.buf);
    log_info("%s %s", method, uri);
}
