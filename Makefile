server = jj_server.o jj_common.o
client = jj_client.o jj_common.o
obj = $(server) $(client)
debug_opt=-g
#debug_opt=

all: $(server) $(client)
	gcc $(debug_opt) -o server $(server)
	gcc $(debug_opt) -o client $(client)

jj_server.o : jj_server.c
	gcc $(debug_opt) -c jj_server.c

jj_common.o : jj_common.c
	gcc $(debug_opt) -c jj_common.c

jj_client.o : jj_client.c
	gcc $(debug_opt) -c jj_client.c

clean :
	rm $(server) jj_client.o server client
