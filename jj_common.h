#ifndef _JJ_COMMON_INCLUDED_
#define _JJ_COMMON_INCLUDED_

#define JJ_OK		0
#define JJ_ERROR	-1
#define JJ_NULL		NULL

#define JJ_BUFFER_SIZE_1K 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <error.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>

int jj_get_file_line_count(const char* file, int* line_count);
void jj_dir(const char* msg);

#endif
