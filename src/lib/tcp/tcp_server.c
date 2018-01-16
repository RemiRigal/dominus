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
#include <arpa/inet.h>

int socket_RV;

void signals_handler(int signal_number)
{
	close(socket_RV);
	fflush(stdout);
	printf("\nClosed cleanly\n");
}

void listener(char* IP, int port)
{
	//struct hostent *hote;
	struct sockaddr_in adr;

	if( (socket_RV=socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		perror("Socket RV failure");
		exit(1);
	}
	
	adr.sin_addr.s_addr = inet_addr(IP);
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);

/*
	hote = gethostbyname(name);
	bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);
*/

	if ( connect(socket_RV,(struct sockaddr *)&adr, sizeof(adr))==-1 )
	{
		perror("Connection failure");
		exit(1);
	}

}

int main(int argc, char *argv[]) {

	// Check correct use and update parameters
    if (argc != 3)
    {
        printf("Listen on a TCP server.\nNeeded 2 arguments but %d given.\nUse this way -> ./listener IP Port\n", argc-1);
        return EXIT_FAILURE;
    }

	// SIGACTION
    struct sigaction action;

    action.sa_handler = signals_handler;
    sigemptyset(& (action.sa_mask));

    sigaction(SIGQUIT, & action, NULL);
    sigaction(SIGINT, & action, NULL);
    // END SIGACTION

    // Server client
    listener(argv[1], atoi(argv[2]));

    // Listening
	char msg;

	do
	{
		msg = EOF;
		read(socket_RV, &msg, 1);
		putchar(msg);
	} while (msg!=EOF);

	close(socket_RV);

	return 0;
}
