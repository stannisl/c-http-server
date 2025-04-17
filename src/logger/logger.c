#include "../../include/logger/logger.h"

void init_logger()
{
#ifdef DEBUG
    log_set_level(LOG_TRACE);
#else
    log_set_level(LOG_WARN);
#endif
}
