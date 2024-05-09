#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define IP_ADDRESS "127.0.0.1"

char* encodeData(char* data) {
    int i;
    char* encodedData = (char*)malloc(strlen(data) + 1);

    for (i = 0; i < strlen(data); i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            encodedData[i] = ((data[i] - 'A' + 4) % 26) + 'A';
        } else {
            encodedData[i] = data[i];
        }
    }

    encodedData[i] = '\0';
    return encodedData;
}

int main() {
    struct sockaddr_in serverAddr;
    int sock = 0;
    char data[1024];
    char* encodedData;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP_ADDRESS, &serverAddr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0'; // Removing trailing newline character

    send(sock, data, strlen(data), 0);
    printf("Data sent to server: %s\n", data);

    read(sock, buffer, 1024);
    printf("Encoded data received from server: %s\n", buffer);

    close(sock);
    return 0;
}

