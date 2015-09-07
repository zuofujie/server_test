#ifndef _JJ_SERVER_INCLUDED_
#define _JJ_SERVER_INCLUDED_

#include "jj_common.h"

int jj_server_startup(int port, int* socket_fd);
int jj_server_accept(int socket_fd);

#endif
