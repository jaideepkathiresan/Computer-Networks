#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int count_words(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    int word_count = 0;
    char buffer[BUFFER_SIZE];

    while (fscanf(file, "%s", buffer) != EOF) {
        word_count++;
    }

    fclose(file);
    return word_count;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Receive file name from client
    if (read(new_socket, buffer, BUFFER_SIZE) < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }

    printf("Received file name: %s\n", buffer);

    // Count the number of words
    int word_count = count_words(buffer);

    // Send the word count back to the client
    if (send(new_socket, &word_count, sizeof(word_count), 0) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }

    printf("Word count sent to the client: %d\n", word_count);

    return 0;
}
