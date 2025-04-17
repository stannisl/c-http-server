#include "../../include/logger/logger.h"

void init_logger()
{
#ifndef DEBUG
    log_set_level(LOG_TRACE);
#else
    log_set_level(LOG_ERROR);
#endif
}
