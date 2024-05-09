#include <stdio.h> /* These are the usual header files */

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>

#include <unistd.h>

#include <stdlib.h>

#define PORT 3550 /*Assigning Port number */

#define BACKLOG 12 /* Number of allowed connections */

int main()

{

int fd; /* file descriptors */

struct sockaddr_in server; /* server's address information */

struct sockaddr_in client; /* client's address information */

int sin_size;

int x;

if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){ /* calls socket() */

printf("socket() error\n");

exit(-1);

}

server.sin_family = AF_INET;

server.sin_port = htons(PORT); /* Remember htons() from "Conversions" section? =) */

server.sin_addr.s_addr = INADDR_ANY; /* INADDR_ANY puts your IP address automatically */

bzero(&(server.sin_zero),8); /* zero the rest of the structure */

if(bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1) /* calls bind() */

{ printf("bind() error\n");

exit(-1);

}

x=listen(fd,BACKLOG) ; /* calls listen() */

if(x==-1)

{

printf("listen() error\n");

exit(-1);

}

else

{

printf("Server is in listening mode \n" );

}

close(fd); /* close fd */

}
