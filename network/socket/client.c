#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <signal.h>
int sockfd;
void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
	printf("signal\n");
	close(sockfd);
	exit(0);
    }
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
	printf("not init the signal\n");
	return 1;
    }
    int portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[10240];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    while (1)
    {
	bzero(buffer,10240);
	n = write(sockfd,buffer,10240);
    }
    if (n < 0) 
         error("ERROR writing to socket");
    close(sockfd);
    return 0;
}
