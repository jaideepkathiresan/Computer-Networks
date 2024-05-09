#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    int word_count = 0;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Get the file name from the user
    printf("Enter the file name: ");
    scanf("%s", buffer);

    // Send the file name to the server
    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }

    // Receive the word count from the server
    if (read(sock, &word_count, sizeof(word_count)) < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }

    printf("Number of words in the file: %d\n", word_count);

    return 0;
}

