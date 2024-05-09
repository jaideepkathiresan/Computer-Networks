#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 4771

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv;
    char buff[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        perror("Error creating socket");
        exit(0);
    }

    printf("Client Socket Created Successfully.\n");

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("Error in connect");
        exit(0);
    }

    printf("Client Socket connected to Server Successfully.\n");

    do
    {
        // Clear the buffer before using it
        memset(buff, 0, sizeof(buff));

        printf("Client: ");
        fgets(buff, 100, stdin);

        // Send message to the server
        write(sockfd, buff, sizeof(buff));

        if (strcmp(buff, "bye\n") == 0)
        {
            printf("Client: %s", buff);
            break; // Exit the loop if the client says bye
        }

        // Clear the buffer before using it
        memset(buff, 0, sizeof(buff));

        // Read the message from the server
        read(sockfd, buff, sizeof(buff));

        printf("From Server: %s\n", buff);

    } while (strcmp(buff, "bye\n") != 0);

    close(sockfd);

    return 0;
}
