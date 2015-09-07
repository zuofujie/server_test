#include "jj_common.h"

int jj_get_file_line_count(const char* file, int* line_count){
	FILE* fp;
	int status;
	char buffer[32];
	char cmd[JJ_BUFFER_SIZE_1K];

	sprintf(cmd, "cat %s | wc -l", file);
	
	fp = popen(cmd, "r");
	if (fp == NULL){
		printf("can not cat file: %s", file);
		return JJ_ERROR;
	}
	fgets(buffer, sizeof(buffer), fp);
	status = pclose(fp);
	if (status == -1){
		printf("get_file_line_count error: %s", file);
		return JJ_ERROR;
	}
	
	*line_count = atoi(buffer);

	return JJ_OK;
}

void jj_die(const char* msg){
	perror(msg);
	exit(JJ_ERROR);
}
