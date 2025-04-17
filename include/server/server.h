#ifndef __INCLUDE_SERVER_SERVER_H_
#define __INCLUDE_SERVER_SERVER_H_

#include "../../libs/mongoose/mongoose.h"
#include "../config/config.h"

typedef enum ErrCode
{
    ERR_OK = 0,
    ERR_MISSING_ENV = 1,
    ERR_INVALID_CREDENTIALS = 2,
    ERR_FILE_NOT_FOUND = 3
} EAppErrCode;

void startServer(struct mg_mgr *mgr,serverConfig_t *config);


// static int process_request();

#endif // __INCLUDE_SERVER_SERVER_H_
