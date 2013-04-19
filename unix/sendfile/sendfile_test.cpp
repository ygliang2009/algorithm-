/*
 * this example display the usage of sendfile syscall.
 */
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

using std::cerr;
using std::endl;
using std::cout;

int main(){
	struct stat buf;
	
	int in_fd = open("in_file",O_RDONLY);
	int out_fd = open("out_file",O_CREAT|O_RDWR,0644);

	if(in_fd < 0 || out_fd < 0){
		cerr << "open in file error" << endl;
		close(in_fd);
		close(out_fd);
		return -1;
	}
	if(fstat(in_fd,&buf) != 0){
		cerr << "stat in_file error" << endl;
		close(in_fd);
		close(out_fd);
		return -2;
	}
	int send_cnt = sendfile(out_fd,in_fd,0,buf.st_size);
	if(send_cnt < 0){
		cerr << "sendfile called error" << endl;
		close(in_fd);
		close(out_fd);
		return -3;
	}else{
		cout << "send bytes:" << send_cnt << endl;
	}
	close(in_fd);
	close(out_fd);
	return 0;
}
