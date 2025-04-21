#include "../../include/server/server.h"
#include "../../include/IO/input.h"
#include "../../include/constants.h"
#include <signal.h>

static volatile sig_atomic_t running = 1;

static void signal_handler(int signum)
{
    running = 0;
    log_info("Получен сигнал %s, производим graceful shutdown...", signum == SIGINT ? "SIGINT" : "SIGTERM");
}

/**
 * @brief Инициализирует подключение в менеджере соединений и настраивает внутренюю конфигурацию данными из конфиг файла
 * @param *srv Server Указатель на настройки внутреннего севрера
 * @param *config serverConfig_t Указатель на конфигурацию сервера из конфиг файла.
 */
void server_init(Server *srv, const serverConfig_t *config)
{
    mg_mgr_init(&srv->mgr);
    srv->config = *config;
    srv->handlers = NULL;
    srv->handlers_count = 0;
    srv->user_data = NULL;
}

/**
 * @brief Добавляет обработчик в конец пула обработчиков.
 * @param *srv Server Указатель на настройки внутреннего севрера
 * @param handler RequestHandler указатель на функцию обработчика.
 */
void server_register_handler(Server *srv, RequestHandler handler)
{
    srv->handlers = realloc(srv->handlers, (srv->handlers_count + 1) * sizeof(RequestHandler));
    srv->handlers[srv->handlers_count++] = handler;
}

/**
 * @brief Главный обработчик событий сервера
 * @param с Указатель на текущее соединение
 * @param ev Код события.
 * @param ev_data Данные события.
 */
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
                log_info("Запрос будет обработан обработчиком %zu: %d", i, status);
        }
        if (status == 0)
        {
            char *data = read_file(NOT_FOUND_PAGE);
            mg_http_reply(c, HTTP_STATUS_CODE_NOT_FOUND, CONTENT_TYPE_HTML, data);
            free(data);
            log_info("Не найден подходящий обработчик 404.");
        }
    }
}

/**
 * @brief Запуск сервера и прослушиванияна на указанном порту
 * @param srv Указатель на настройки внутреннего сервера
 */
void server_start(Server *srv)
{
    char url[256];
    snprintf(url, sizeof(url), "http://localhost:%d", srv->config.port);

    struct mg_connection *conn = mg_http_listen(&srv->mgr, url, event_handler, srv);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if (conn == NULL)
        log_error("Ошибка при старте прослушивания на %s", url);
    else
    {
        log_info("Сервер запущен на %s", url);
        for (; running;)
            mg_mgr_poll(&srv->mgr, 1000);
    }
}

/**
 * @brief Остановка сервера и очистка ресурсов
 * @param srv Указатель на настройки внутреннего сервера
 */
void server_stop(Server *srv)
{
    mg_mgr_free(&srv->mgr);
    free(srv->handlers);

    log_info("Сервер успешно остановлен.");
}
