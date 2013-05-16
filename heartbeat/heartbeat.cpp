#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>
#include <stdlib.h>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define BUFSIZ	1024

using namespace std;
using boost::shared_ptr;
using boost::lexical_cast;

string server_ip("");
int server_port  = 0;

class Server{
	string ip;
	u_int32_t port;
	bool status;
	struct sockaddr_in *sock_addr;
	public:
		int sockfd;
		shared_ptr<string> rcvbuf;
		Server(string,u_int32_t);
		void setIp(string ip){
			this->ip = ip;
		}
		string getIp(){
			return this->ip;
		}
		void setPort(u_int32_t port){
			this->port = port;
		}
		u_int32_t getPort(){
			return this->port;
		}
		bool send(string buffer);
		void recv();		
		~Server();
};

Server::Server(string ip_str,u_int32_t port_int):status(false),ip(ip_str),port(port_int){
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd > 0){
		this->sockfd = fd;
		this->sock_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
		this->sock_addr->sin_family = AF_INET;
		struct hostent *ent = gethostbyname(ip.c_str());
		if(ent != NULL){
			memcpy(&(sock_addr->sin_addr),ent->h_addr,ent->h_length);
			sock_addr->sin_port = htons(this->port);
		}
		int conn_status = connect(this->sockfd,(struct sockaddr *)sock_addr,sizeof(struct sockaddr_in));
		this->status = true;
	}
	else{
		this->status = false;
	}
}

bool Server::send(string buffer){
	bool wr_status = false;
	if(write(this->sockfd,buffer.c_str(),buffer.size()) > 0){
		wr_status = true;
	}
	return wr_status;
}

void Server::recv(){
	char rcv_buf[BUFSIZ];
	string buf("");
	int count = 0;
	do{
		count = read(this->sockfd,rcv_buf,BUFSIZ);
		if(count > 0)
			buf.append(rcv_buf);
	}while(count);
	shared_ptr<string> buffer(new string(buf));
	this->rcvbuf = buffer;
}


Server::~Server(){
	close(this->sockfd);
	free(sock_addr);
}

void alarm_test(int signo){
	cout << "------------ heartbeat ------------" << endl;
	Server server(server_ip,server_port);
	bool snd_res = server.send("GET / HTTP/1.0\r\n\r\n");
	server.recv();
	cout << *(server.rcvbuf) << endl;
}

void process(){
	cout << "----------- process event ----------" << endl;
}

int main(int argc, char* argv[]){
	if(argc != 3){
		cout << "heartbeat ip port" << endl;
		return 0;
	}
	server_ip = argv[1];
	server_port = lexical_cast<int>(argv[2]);	
	signal(SIGALRM,alarm_test);
	while(1){
		alarm(3);
		process();
		pause();
	}
}
