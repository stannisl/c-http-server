#ifndef __INCLUDE_SERVER_HANDLERS_H_
#define __INCLUDE_SERVER_HANDLERS_H_

#include "../config/config.h"
#include "../types.h"

int handleStaticResource(struct mg_connection *conn, struct mg_http_message *message);
int handleFormSubmission(struct mg_connection *conn, struct mg_http_message *message);
int handleLoggingRequest(struct mg_connection *conn, struct mg_http_message *message);
int handleSubmitRating(struct mg_connection *conn, struct mg_http_message *message);

#endif // __INCLUDE_SERVER_HANDLERS_H_
