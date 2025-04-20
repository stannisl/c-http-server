#ifndef __INCLUDE_CONFIG_CONFIG_H
#define __INCLUDE_CONFIG_CONFIG_H

#include "../types.h"

/**
 * @brief Функция для парсинга ini конфига
 * @param filename Название файла конфига
 * @param config Указатель на структуру внешнего конфига.
 * @return 0, если успех. 3, если файл не найден.
 */
int parseConfig(const char *filename, serverConfig_t *serverConfig);

#endif // __INCLUDE_CONFIG_CONFIG_H
