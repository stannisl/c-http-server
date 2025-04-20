#include "../../../include/IO/input.h"
#include "../../../include/constants.h"
#include "../../../include/server/handlers.h"
#include "../../../include/server/server.h"

/**
 * @brief вспомогательная функция для экстракции значения query параметра в double
 * @param body тело запроса
 * @param *name название переменной query параметра
 *
 * @return значение параметра, 0 если неверное значение.
 */
static double parse_rating(struct mg_str body, const char *name)
{
    char buf[50];
    int len = mg_http_get_var(&body, name, buf, sizeof(buf));
    return (len > 0) ? atof(buf) : 0;
}

/**
 * @brief Обработчик POST события по высчету рейтинга
 * @param conn текущее соединение mg_connection
 * @param *message текущий запроc mg_http_message
 *
 * @return 200 если запрос был обработан этим обработчиком
 *            0 если запрос не был обработан.
 */
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
        char *fileData = read_file(SATISFACTION_RESULT_PAGE);
        snprintf(html, sizeof(html), fileData, average, (int)rating1, (int)rating2, (int)rating3, (int)rating4);
        free(fileData);

        mg_http_reply(conn, HTTP_STATUS_CODE_OK, "Content-Type: text/html\r\n", "%s", html);
        http_code = HTTP_STATUS_CODE_OK;
    }
    return http_code;
}
