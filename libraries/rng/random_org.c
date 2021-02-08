/* random_org.c
 * Description: Getting some random numbers from random.org
 * Author: Jochen Brenner (jochen_brenner@gmx.de)
 * Created: August 16th, 2002
 * Compile: gcc -o random_org.o random_org.c
 * Example: ./random_org.o  1 10 
 * Info: I tested only on freeBSD 4.4 but it should work on other linux/unix-systems
 * and windows too
 * Licence: GPL
 * Wish: Please leave me a message if part of this code fit your effort in any way
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
/* Headerfiles for Windows */
#include <winsock.h>
#include <io.h>

#else
/* Headerfiles for Unix/Linux */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket(s) close(s)
#endif

/* http used to be requested on port 80 */
#define HTTP_PORT 80

/* random numbers used to be requested on random.org :-) */
#define RANDOM_ORG "www.random.org"

/****************** MAIN *********************/
int main( int argc, char **argv)
{
    struct sockaddr_in server;
    struct hostent *host_info;
    unsigned long addr;
    int sock;
    char buffer[8192];
    int count;
    
    
#ifdef _WIN32  
    /* init TCP for Windows ("winsock") */
    short wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD (1, 1);
    if (WSAStartup (wVersionRequested, &wsaData) != 0) {
        fprintf( stderr, "Failed to init windows sockets\n");
        exit(1);
    }
#endif

    /* correct comandline? */
    if (argc != 3) {
        fprintf( stderr, "usage: %s min max\n", argv[0]);
        exit(1);
    }

    /* create socket */
    sock = socket( PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror( "failed to create socket");
        exit(1);
    }

    /* Create socketadress of Server
     * it is type, IP-address and portnumber */
    memset( &server, 0, sizeof (server));
    /* convert the Servername to a IP-Adress */
    host_info = gethostbyname( RANDOM_ORG);
    if (NULL == host_info) {
        fprintf( stderr, "unknown server: %s\n", RANDOM_ORG);
        exit(1);
    }
    memcpy( (char *)&server.sin_addr, host_info->h_addr, host_info->h_length);

    server.sin_family = AF_INET;
    server.sin_port = htons( HTTP_PORT);

    /* connect to the server */
    if ( connect( sock, (struct sockaddr*)&server, sizeof( server)) < 0) {
        perror( "can't connect to server");
        exit(1);
    }

    /* create and send the http GET request */
    sprintf( buffer, "GET /cgi-bin/randnum?num=100&min=%s&max=%s HTTP/1.0\nHost: %s\n\n",
                argv[1], argv[2], RANDOM_ORG);
    send( sock, buffer, strlen( buffer), 0);

    /* get the answer from server and put it out to stdout */
    do {
        count = recv( sock, buffer, sizeof(buffer), 0);
        write( 1, buffer, count);
    }
    while (count > 0);

    /* close the connection to the server */
    closesocket( sock);
    return count;
}
