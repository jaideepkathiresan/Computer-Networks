#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER];

    // Create the client socket
    if ((client_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect the client socket to the server
    if (connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    while(1) {
        // Send a message to the server
        printf("Enter your message: ");
        fgets(buffer, MAX_BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // remove trailing newline
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            perror("send failed");
            break;
        }

        if(strcmp(buffer, "exit") == 0) {
            break;
        }

        // Receive and print the server's message
        if (recv(client_socket, buffer, MAX_BUFFER, 0) < 0) {
            perror("recv failed");
            break;
        }
        printf("Server: %s\n", buffer);
    }

    // Close the socket
    close(client_socket);

    return 0;
}
