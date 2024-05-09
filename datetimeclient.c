#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 4771

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[100];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Error creating socket");
        return 1;
    }

    // Initialize server address structure
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Assuming server is on the same machine

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error in connect");
        return 1;
    }

    while (1)
    {
        printf("Enter 'get_datetime' to get date and time, or 'exit' to exit: ");
        fgets(buffer, sizeof(buffer), stdin);
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define PORT 4771

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[100];
    time_t rawtime;
    struct tm *timeinfo;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Error creating socket");
        return 1;
    }

    // Initialize server address structure
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error in bind");
        return 1;
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0)
    {
        perror("Error in listen");
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept connections
    int len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (connfd < 0)
    {
        perror("Error in accept");
        return 1;
    }

    printf("Client connected...\n");

    while (1)
    {
        bzero(buffer, sizeof(buffer));

        // Read client request
        read(connfd, buffer, sizeof(buffer));

        if (strcmp(buffer, "get_datetime\n") == 0)
        {
            // Get current date and time
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(buffer, sizeof(buffer), "Date and Time: %Y-%m-%d %H:%M:%S", timeinfo);

            // Send date and time to client
            write(connfd, buffer, sizeof(buffer));
        }
        else if (strcmp(buffer, "exit\n") == 0)
        {
            printf("Client requested to exit.\n");
            break;
        }
        else
        {
            // Invalid request
            write(connfd, "Invalid request\n", sizeof("Invalid request\n"));
        }
    }

    close(connfd);
    close(sockfd);

    return 0;
}
        // Send request to the server
        write(sockfd, buffer, sizeof(buffer));

        if (strcmp(buffer, "exit\n") == 0)
        {
            printf("Exiting client...\n");
            break;
        }

        // Receive and print server response
        read(sockfd, buffer, sizeof(buffer));
        printf("Server response: %s\n", buffer);
    }

    close(sockfd);

    return 0;
}



