#include "../../../include/IO/input.h"
#include "../../../include/constants.h"
#include "../../../include/server/handlers.h"
#include "../../../include/server/server.h"

static double parse_rating(struct mg_str body, const char *name)
{
    char buf[50];
    int len = mg_http_get_var(&body, name, buf, sizeof(buf));
    return (len > 0) ? atof(buf) : 0;
}

int handleSubmitRating(struct mg_connection *conn, struct mg_http_message *message)
{
    int http_code = 0;

    if (!mg_strcmp(message->uri, mg_str("/submit-ratings")) && !mg_strcmp(message->method, mg_str("POST")))
    {
        double rating1 = parse_rating(message->body, "sat-range1");
        double rating2 = parse_rating(message->body, "sat-range2");
        double rating3 = parse_rating(message->body, "sat-range3");
        double rating4 = parse_rating(message->body, "sat-range4");

        double average = (rating1 + rating2 + rating3 + rating4) / 4.0;

        char html[4096];
        snprintf(html, sizeof(html), read_file(SATISFACTION_RESULT_PAGE), average, (int)rating1, (int)rating2, (int)rating3, (int)rating4);

        mg_http_reply(conn, HTTP_STATUS_CODE_OK, "Content-Type: text/html\r\n", "%s", html);
        http_code = HTTP_STATUS_CODE_OK;
    }
    return http_code;
}
