#include <stdio.h>      // input and output
#include <stdlib.h>     // standard library
#include <sys/socket.h> // socket definitions
#include <unistd.h>
#include <sys/types.h>  // basic system data types
#include <netinet/in.h> // sockaddr_in and other internet definitions
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAXLINE 4096

int main(int argc, char const *argv[])
{
    // declaritions
    size_t socket_fd;
    struct sockaddr_in server_address;
    char receiveline[MAXLINE + 1];

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, NULL)) < 0)
        // TODO: check the errno and return more meaningful error codes
        printf("socket error: failed to init a socket");
        exit(1);

    /* 
     * Ip address of the server must be provided.
     */
    if (argc != 2)
    {
        printf("Ip address of ther server must be provided\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address)); // initialize with zeros

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(13); // the port number of the daytime server

    // convert the IP address from a string(dot notation), to a binary representation
    if (inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0)
    {
        if (errno == EAFNOSUPPORT)
            printf("invalid address provided");
        else
            printf("error occurred converting address");

        exit(1);
    }

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(&server_address) < 0))
    {
        printf("failed to connect socket");
        // TODO: check the error codes in errno and return meaningful error message
        exit(1);
    }

    int n;
    while ((n = read(socket_fd, receiveline, MAXLINE) > 0))
    {
        receiveline[n] = NULL; // null terminate
        if (fputs(receiveline, stdout) == EOF)
        {
            // TODO: return a better error message
            printf("error when writing the server's response to the output device");
            exit(1);
        }
    }
    if(n == -1){
        // TODO: check errno and return a better error message
        printf("error: reading from the socket");
        exit(1);
    }

    // TODO: close sockets and release all the resources used.

    return 0;
}
