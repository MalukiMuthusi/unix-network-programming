#include <stdio.h> // input and output
#include <stdlib.h> // standard library
#include <sys/socket.h> // socket definitions
#include <unistd.h>
#include <sys/types.h> // basic system data types
#include <netinet/in.h> // sockaddr_in and other internet definitions

int main(int argc, char const *argv[])
{
    size_t socket_fd;
    struct  sockaddr_in server_address;
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, NULL)) < 0)
        printf("socket error: failed to init a socket");
    
    /* 
     * Ip address of the server must be provided.
     */
    if (argc != 2)
    {
        printf("Ip address of ther server must be provided\n");
    }

    
    return 0;
}
