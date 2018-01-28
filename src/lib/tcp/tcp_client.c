#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <strings.h> /* pour bcopy */
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>

int socket_RV;

void connect_to_server(char* IP, int port)
{
	//struct hostent *hote;
	struct sockaddr_in adr;

	if ((socket_RV = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
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

void send_remote_message(char* IP, int port, char* message)
{
    // Server host
    connect_to_server(IP, port);

	// Sending msg
    char msg;
    //do 
    //{
    //    msg = getchar();
    //    send(socket_RV, &msg, 1, 0);
    //} while (msg != EOF);
	send(socket_RV, message, strlen(message), 0);
    close(socket_RV);
}

int main(int argc, char *argv[])
{	
    if (argc != 4)
    {
        printf("Send a message to a TCP server.\nNeeded 3 arguments but %d given.\nUse this way -> ./client Ip Port Message\n", argc-1);
        return EXIT_FAILURE;
    }
	
	send_remote_message(argv[1], atoi(argv[2]), argv[3]);

	return 0;
}


