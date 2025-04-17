#ifndef __INCLUDE_LOG_LOGGER_H__
#define __INCLUDE_LOG_LOGGER_H__

#include "../types.h"

void init_logger();
void logRequest(struct mg_http_message *hm);

#endif
