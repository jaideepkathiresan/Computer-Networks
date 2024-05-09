#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <string.h>
#define PORTNO 2000
int main(){
	int sockfd,i=PORTNO;

	struct sockaddr_in myaddr; /* Builtin structure for internet address */

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("Socket Creation Error\n");
	}
	myaddr.sin_family=AF_INET; /* Structure variable definition */
	myaddr.sin_port=htons(PORTNO);
	myaddr.sin_addr.s_addr=INADDR_ANY;
	memset(&(myaddr.sin_zero),'\0',8); /* fills with constant byte to remaining space */
	if(bind(sockfd,(struct sockaddr *)&myaddr,sizeof(struct sockaddr))!=-1){
		printf("Socket is Binded at port %d\n",i);
	}
	else{
		printf("Binding Error\n");
	}
}
