#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
	int sockfd1,sockfd2;
	sockfd1=socket(AF_INET,SOCK_STREAM,0);
	sockfd2=socket(PF_INET,SOCK_DGRAM,0);
	if (sockfd1==-1){
		printf("Socket 1 not created");
	}
	else{
		printf("Socket 1 created and \t socket 1 file descriptor value is %d\n",sockfd1);
		if (sockfd2==-1){
			printf("Socket 2 not created");
		}
		else{
			printf("Socket 2 created and \t socket 2 file descriptor value is %d\n",sockfd2);
		}
	}
}
