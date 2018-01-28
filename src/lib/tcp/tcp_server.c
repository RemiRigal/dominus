#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <strings.h> /* pour bcopy */
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>

int socket_service;
int tcp_server;

struct sockaddr_in adr;
socklen_t lgadresse;

void signals_handler(int signal_number)
{
    close(socket_service);
    close(tcp_server);
	fflush(stdout);
	printf("\nClosed cleanly\n");
    exit(1);
}

int init_server(int port)
{
	int socket_RV;
	int socket_service;

	if ((socket_RV = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket RV failure");
		exit(1);
	}

	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	adr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(socket_RV, (struct sockaddr *) &adr, sizeof(adr))==-1)
	{
		perror("Binding failure");
		exit(1);
	}			

	if (listen(socket_RV,1)==-1)
	{
		perror("Listening failure");
		exit(1);
	}

    return socket_RV;
}

void start_server(int port)
{
    tcp_server = init_server(port); 
    do
    {
        socket_service = accept(tcp_server,(struct sockaddr *)&adr, &lgadresse);

        // Listening
	    char msg;
        do
	    {
		    msg = EOF;
		    recv(socket_service, &msg, 1, 0);
		    putchar(msg);
	    } while (msg!=EOF);

        close(socket_service);
    } while (1);
}

int main(int argc, char *argv[]) {

	// Check correct use and update parameters
    if (argc != 2)
    {
        printf("Host a TCP server.\nNeeded 1 argument but %d given.\nUse this way -> ./listener Port\n", argc-1);
        return EXIT_FAILURE;
    }

	// SIGACTION
    struct sigaction action;

    action.sa_handler = signals_handler;
    sigemptyset(& (action.sa_mask));

    sigaction(SIGQUIT, & action, NULL);
    sigaction(SIGINT, & action, NULL);
    // END SIGACTION

    start_server(atoi(argv[1]));

	return 0;
}
