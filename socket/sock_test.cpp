#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdlib>

using namespace std;

int main(int argc,char *argv[]){
	char buffer[BUFSIZ];
	if(argc < 2){
		cout << "sock_test host" << endl;
		return 0;
	}
	struct sockaddr_in sock;
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		cout << strerror(errno) << endl;
		return -1;
	}
	sock.sin_port = htons(80);
	sock.sin_family = AF_INET;
	struct hostent *ent = gethostbyname(argv[1]);
	memcpy(&(sock.sin_addr),ent->h_addr,ent->h_length);
	if(connect(fd,(struct sockaddr *)&sock,sizeof(struct sockaddr_in)) < 0){
		cout << strerror(errno) << endl;
		return -1;
	}
	printf("sending...\n");
	char send_buffer[] = "GET / HTTP/1.0\r\n\r\n";
	int write_n = 0;
	if((write_n = write(fd,send_buffer,strlen(send_buffer))) <= 0){
		cout << strerror(errno) << endl;
		return -1;
	}
	printf("sending count: %d\treceving...\n",write_n);
	int n = 0;
	while((n = read(fd,buffer,BUFSIZ)) > 0){
		cout << "n:" << n << "\tbuffer:" << buffer << endl;
	}
	exit(0);
}
