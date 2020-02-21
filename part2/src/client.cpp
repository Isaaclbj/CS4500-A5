#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <arpa/inet.h>
#include <poll.h>

void*
get_msg(void *ss)
{
    int client = *(int*) ss;
    delete (int*)ss;
    while(1)
    {
        char buffer[4096] = {0};
        int len = read(client, buffer, 4096);
        buffer[len] = 0;
        printf("%s\n", buffer);
        fflush(stdout);
        fflush(stdin);
    }
    return 0;
}

int
main(int argc, char**argv)
{
    int sock = 0;
    struct sockaddr_in serv;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET, argv[2], &serv.sin_addr);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

    if(connect(sock, (struct sockaddr *) &serv, sizeof(serv)) == -1)
    {
        perror("failed to connect");
        exit(-1);
    }
    printf("connected to %d\n", sock);
    pthread_t thread;
    int *pass = new int;
    *pass = sock;
    pthread_create(&thread, 0, get_msg, (void*)pass);

    while(1)
    {
        char in_msg[4096];
        scanf("%[^\n]", in_msg);
        send(sock, in_msg, 4096, 0);
    }
    exit(0);
}