#ifndef __INCLUDE_SERVER_SERVER_H_
#define __INCLUDE_SERVER_SERVER_H_

#include "../config/config.h"
#include "../types.h"

void server_init(Server *srv, const serverConfig_t *config);
void server_register_handler(Server *srv, RequestHandler handler);
void server_start(Server *srv);
void server_stop(Server *srv);

#endif // __INCLUDE_SERVER_SERVER_H_
