#include "jj_common.h"

int jj_server_startup(int port, int* socket_fd){
	struct sockaddr_in addr;

	*socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*socket_fd < 0){
		perror("socket error");
		return JJ_ERROR;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family			= AF_INET;
	addr.sin_port			= htons(port);
	addr.sin_addr.s_addr	= htonl(INADDR_ANY);

	if (bind(*socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0 ){
		perror("bind error");
		return JJ_ERROR;
	}

	if (listen(*socket_fd, 5) < 0){
		perror("listen error");
		return JJ_ERROR;
	}

	return JJ_OK;
}

int jj_server_accept(int socket_fd){
	int n;
	int time1, time2;
	char buf[JJ_BUFFER_SIZE_1K];
	
	time1 = time((time_t*)NULL);

	while(1){
		n = recv(socket_fd, buf, JJ_BUFFER_SIZE_1K, 0);
		if (n > 0){
			buf[n] = '\0';
			printf("recv data: %s\n", buf);
			sprintf(buf, "send message: %d\n", 2);
			send(socket_fd, buf, JJ_BUFFER_SIZE_1K, 0);

			//close(socket_fd);
		}
		time2 = time((time_t*)NULL);
		if (time2 - time1 > 10){
			exit(0);
		}
	}
}

void signal_handle(int signal){
	pid_t pid;
	int stat;
	while((pid = waitpid(0, &stat, WNOHANG)) > 0){
		printf("child %d exit\n", pid);
	}
}

int main(int argc, char* argv[]){
	int port = 6666;
	int socket_fd = -1;
	int client_socket;
	struct sockaddr_in client_addr;
	int client_addr_length;
	pid_t pid;
	struct sigaction action;

	if (jj_server_startup(port, &socket_fd) != JJ_OK){
		perror("jj_startup error");
		return JJ_ERROR;
	}

	action.sa_handler = &signal_handle;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_flags |= SA_RESTART;
	sigaction(SIGCHLD, &action, NULL);

	client_addr_length = sizeof(client_addr);

	while(1){
		client_socket = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_length);
		if (client_socket < 0){
			perror("connect error");
			return JJ_ERROR;
		}

		if (client_socket){
			pid = fork();
			if (pid > 0){
				close(client_socket);
			} else if (pid == 0){
				close(socket_fd);
				jj_server_accept(client_socket);
			} else {
				perror("fork error");
				return JJ_ERROR;
			}
		}
	}

	close(socket_fd);

	return JJ_OK;
}
