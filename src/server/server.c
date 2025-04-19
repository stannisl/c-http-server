#include "../../include/server/server.h"
#include "../../include/constants.h"
#include "../../include/IO/input.h"

void server_init(Server *srv, const serverConfig_t *config)
{
    mg_mgr_init(&srv->mgr);
    srv->config = *config;
    srv->handlers = NULL;
    srv->handlers_count = 0;
    srv->user_data = NULL;
}

void server_register_handler(Server *srv, RequestHandler handler)
{
    srv->handlers = realloc(srv->handlers, (srv->handlers_count + 1) * sizeof(RequestHandler));
    srv->handlers[srv->handlers_count++] = handler;
}

static void event_handler(struct mg_connection *c, int ev, void *ev_data)
{
    Server *srv = (Server *)c->fn_data;

    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;

        int status = 0;
        for (size_t i = 0; !status && i < srv->handlers_count; i++)
        {
            status = srv->handlers[i](c, hm);
            if (status != 0)
            {
                log_info("Processed by handler %zu: %d", i, status);
            }
        }
        log_info("status at end is %d", status);
        if (status == 0)
            mg_http_reply(c, HTTP_STATUS_CODE_NOT_FOUND, CONTENT_TYPE_HTML, read_file(NOT_FOUND_PAGE));
    }
}

void server_start(Server *srv)
{
    char url[256];
    snprintf(url, sizeof(url), "http://localhost:%d", srv->config.port);

    struct mg_connection *conn = mg_http_listen(&srv->mgr, url, event_handler, srv);
    if (conn == NULL)
    {
        log_error("Failed to start listener on %s", url);
    }
    else
    {
        log_info("Server started at %s", url);
        for (;;)
            mg_mgr_poll(&srv->mgr, 1000);
    }
}

void server_stop(Server *srv)
{
    mg_mgr_free(&srv->mgr);
    free(srv->handlers);

    log_info("Server stopped");
}
