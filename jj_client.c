#include "jj_common.h"

int main(int argc, char* argv[]){
	int port = 6666;
	int socket_fd;
	int n;
	char buf[JJ_BUFFER_SIZE_1K];
	struct sockaddr_in addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0){
		perror("socket error");
		return JJ_ERROR;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port	= htons(port);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		perror("connect error");
		return JJ_ERROR;
	}

	sprintf(buf, "send message: %d", 1);
	send(socket_fd, buf, JJ_BUFFER_SIZE_1K, 0);
	sleep (3);
	sprintf(buf, "send message: %d", 2);
	send(socket_fd, buf, JJ_BUFFER_SIZE_1K, 0);
	sleep (3);
	sprintf(buf, "send message: %d", 3);
	send(socket_fd, buf, JJ_BUFFER_SIZE_1K, 0);
	sleep (3);
	recv(socket_fd, buf, JJ_BUFFER_SIZE_1K, 0);
	printf("%s\n", buf);

	close(socket_fd);

	return JJ_OK;
}
