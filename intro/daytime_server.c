// TODO: use single header file and avoid copy pasting.

// included in most files
#include <stdio.h>      // input and output
#include <stdlib.h>     // standard library
#include <sys/socket.h> // socket definitions
#include <unistd.h>
#include <sys/types.h>  // basic system data types
#include <netinet/in.h> // sockaddr_in and other internet definitions
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

// common macros
#define MAXLINE 4096

// includes specific to this program
#include <time.h>

int main(int argc, char const *argv[])
{
    int listen_fd, connect_fd;
    struct sockaddr_in server_address;
    char buffer[MAXLINE];

    if ((listen_fd = (socket(AF_INET, SOCK_STREAM, 0))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("socket error: failed to init a socket");
        exit(1);
    }
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(13);

    /* assigning a name to a socket to a socket */
    if ((bind(listen_fd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to assign a name to the socket\n");
        printf("error code: %s\n", strerror(errno));
        exit(1);
    }

    /* mark the passive socket that will be used to accept incoming connection requests */
    if ((listen(listen_fd, 10) < 0))
    {
        // TODO: check the errno and return more meaningful error codes
        printf("failed to mark the fd to be used by the socket");
        exit(1);
    }

    for (;;)
    {
        if ((connect_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL)) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to accept connection");
            exit(1);
        }

        time_t ticks;
        if (ticks = time(NULL) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to get current time");
            exit(1);
        }

        if (snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks)) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write time to the buffer");
            exit(1);
        }

        if (write(connect_fd, buffer, strlen(buffer)) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write time to the socket");
            exit(1);
        }

        if (close(connect_fd) < 0)
        {
            // TODO: check the errno and return more meaningful error codes
            printf("failed to write time to the socket");
            exit(1);
        }
    }
    return 0;
}
