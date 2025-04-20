#ifndef __INCLUDE_LOG_LOGGER_H__
#define __INCLUDE_LOG_LOGGER_H__

#include "../types.h"

/**
 * @brief Функция устанавливающая уроверь логирования
 */
void init_logger();

/**
 * @brief Функция логирования запросов
 * @param hm указатель на http данные запроса.
 */
void logRequest(struct mg_http_message *hm);

#endif
