#include "../../include/server/server.h"
#include "../../include/logger/logger.h"
#include "../../include/IO/input.h"
#include "../../include/constants.h"

static int get_main_page(struct mg_connection *c) {
    mg_http_reply(c, 200, CONTENT_TYPE_HTML, read_file(SATISFACTION_FORM_HTML));
    return 200;
}

static int not_found_page(struct mg_connection *c) {
    mg_http_reply(c, 404, CONTENT_TYPE_HTML, read_file(NOT_FOUND_PAGE));
    return 404;
}


static int process_request(struct mg_connection *c, struct mg_http_message *hm) {
    int requestCode = 500;

    if (!mg_strcmp(hm->uri, mg_str("/"))) {
        log_debug("%zu %zu", mg_str("/").len, hm->uri.len);
        requestCode = get_main_page(c);
    } else {
        log_debug("Path not found");
        requestCode = not_found_page(c);
    }

    return requestCode;
}


static void requestHandler(struct mg_connection *c,int ev,void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        char uri[256], method[10];
        snprintf(uri, hm->uri.len+1, "%s", hm->uri.buf);
        snprintf(method, hm->method.len+1, "%s", hm->method.buf);

        int requestCode = process_request(c, hm);

        log_trace("%s %s %d", uri, method, requestCode);
    }
}


void startServer(struct mg_mgr *mgr,serverConfig_t *config) {
    mg_mgr_init(mgr);

    char url[256];
    sprintf(url, "http://localhost:%d", config->port);

    mg_http_listen(mgr, url, requestHandler, NULL);
    log_trace("Server started at %s", url);

    for (;;) mg_mgr_poll(mgr, 1000);
}
