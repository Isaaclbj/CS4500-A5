#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
// #include <pthread.h>
#include <assert.h>

/*
    some pieces of code are based on the example code,
    provided on piazza.
*/

static const int BUFFER_SIZE = 4096;
static const int PORT = 8080;

// print an error message
// void perr(int em)
// {
//     printf("\nProgram error: %d\n", em);
// }


int
main(const int argc, const char **argv)
{
    int server_fd, sock, rv, clients[32], maxsd, sd;
    struct sockaddr_in adr;
    int opt = 1;
    int addr_len = sizeof(adr);
    char buffer[BUFFER_SIZE] = {0};
    //set of socket fds
    fd_set readfds;

    // create fd
    assert((server_fd = socket(AF_INET, SOCK_STREAM, 0)) != 0);

    // init clients
    for(int ii = 0; ii < 32; ii++)
    {
        clients[ii] = 0;
    }

    // binding socket to port
    assert(setsockopt(server_fd, SOL_SOCKET, 
        SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0);
    // 
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = INADDR_ANY;
    adr.sin_port = htons(PORT);
    assert(bind(server_fd, (struct sockaddr *) &adr, 
        sizeof(adr)) >= 0);

    puts("socket created");
    puts("start listening");
    
    assert(listen(server_fd, 3) >= 0);

    while(1)
    {
        // zero out fds
        FD_ZERO(&readfds);

        // add server to socket set
        FD_SET(server_fd, &readfds);
        maxsd = server_fd;

        for(int ii = 0; ii < 32; ii++)
        {
            sd = clients[ii];

            if(sd > 0)
            {
                FD_SET(sd, &readfds);
            }

            if(sd > maxsd)
            {
                maxsd = sd;
            }
        }
        
        
    }

}