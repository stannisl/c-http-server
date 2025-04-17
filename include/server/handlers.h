#ifndef __INCLUDE_SERVER_HANDLERS_H_
#define __INCLUDE_SERVER_HANDLERS_H_

#include "../../libs/mongoose/mongoose.h"
#include "../config/config.h"
#include <stdlib.h>

typedef int (*RequestHandler)(struct mg_connection *conn, struct mg_http_message *message);

int handleStaticResource(struct mg_connection *conn, struct mg_http_message *message);
int handleNotFound(struct mg_connection *conn, struct mg_http_message *message);
int handleFormSubmission(struct mg_connection *conn, struct mg_http_message *message);

#endif // __INCLUDE_SERVER_HANDLERS_H_
