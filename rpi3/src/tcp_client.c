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

int server(int port)
{
	int socket_RV;
	int socket_service;

	struct sockaddr_in adr;
	socklen_t lgadresse;

	if((socket_RV=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket RV failure");
		exit(1);
	}

	adr.sin_family=AF_INET;
	adr.sin_port=htons(port);
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
	
	// Wait for client
	socket_service = accept(socket_RV,(struct sockaddr *)&adr, &lgadresse);
	close(socket_RV);

	return socket_service;
}

int main(int argc, char *argv[])
{	
    if (argc != 2)
    {
        printf("Host a TCP server.\nNeeded 1 arguments but %d given.\nUse this way -> ./listener Port\n", argc-1);
        return EXIT_FAILURE;
    }

	int socket_service;
	
	// Server host
	socket_service = server(atoi(argv[1]));

	// Sending msg
	char msg;

	do
	{
		msg = getchar();
		write(socket_service, &msg, 1);
	} while (msg!=EOF);

	return 0;
}


