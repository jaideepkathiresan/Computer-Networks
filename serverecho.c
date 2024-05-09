#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[MAX_BUFFER];

    // Create the server socket
    if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the server socket to our specified IP and port
    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen on the socket
    if (listen(server_socket, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept a connection from the client
    addr_size = sizeof(client_addr);
    if ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_size)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    while(1) {
        // Receive and print the client's message
        if (recv(client_socket, buffer, MAX_BUFFER, 0) < 0) {
            perror("recv failed");
            break;
        }
        printf("Client: %s\n", buffer);

        if(strcmp(buffer, "exit") == 0) {
            break;
        }

        // Send a message back to the client
        printf("Enter your message: ");
        fgets(buffer, MAX_BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // remove trailing newline
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            perror("send failed");
            break;
        }
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
