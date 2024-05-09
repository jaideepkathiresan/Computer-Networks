#include <stdio.h>
#include <arpa/inet.h>

void classfulAddressing(const char *ipAddress) {
    struct in_addr addr;
    
    if (inet_pton(AF_INET, ipAddress, &addr) <= 0) {
        printf("Invalid IP address\n");
        return;
    }

    unsigned int ip = ntohl(addr.s_addr);
    unsigned int firstAddress = (ip & 0x80000000) | 1;
    unsigned int lastAddress = (ip | 0x7FFFFFFF);
    unsigned int numHosts = (1U << 31) - 2;

    printf("Classful addressing - First address: %d.%d.%d.%d\n", (firstAddress >> 24) & 0xFF, (firstAddress >> 16) & 0xFF, (firstAddress >> 8) & 0xFF, firstAddress & 0xFF);
    printf("Classful addressing - Last address: %d.%d.%d.%d\n", (lastAddress >> 24) & 0xFF, (lastAddress >> 16) & 0xFF, (lastAddress >> 8) & 0xFF, lastAddress & 0xFF);
    printf("Classful addressing - Number of hosts: %u\n", numHosts+2);
}

void classlessAddressing(const char *ipAddress, int mask) {
    struct in_addr addr;
    
    if (inet_pton(AF_INET, ipAddress, &addr) <= 0) {
        printf("Invalid IP address\n");
        return;
    }

    unsigned int ip = ntohl(addr.s_addr);
    unsigned int maskValue = 0xFFFFFFFFU << (32 - mask);
    unsigned int networkAddress = ip & maskValue;
    unsigned int broadcastAddress = networkAddress | ~maskValue;
    unsigned int numHosts = (1U << (32 - mask)) - 2;

    printf("Classless addressing - Network address: %d.%d.%d.%d\n", (networkAddress >> 24) & 0xFF, (networkAddress >> 16) & 0xFF, (networkAddress >> 8) & 0xFF, networkAddress & 0xFF);
    printf("Classless addressing - Broadcast address: %d.%d.%d.%d\n", (broadcastAddress >> 24) & 0xFF, (broadcastAddress >> 16) & 0xFF, (broadcastAddress >> 8) & 0xFF, broadcastAddress & 0xFF);
    printf("Classless addressing - Number of hosts: %u\n", numHosts+2);
}

int main() {
    int choice;
    char ipAddress[20];
    int mask;

    printf("Enter 1 for classful addressing or 2 for classless addressing: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the IP address: ");
        scanf("%s", ipAddress);
        classfulAddressing(ipAddress);
    } else if (choice == 2) {
        printf("Enter the IP address: ");
        scanf("%s", ipAddress);
        printf("Enter the mask value: ");
        scanf("%d", &mask);
        classlessAddressing(ipAddress, mask);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}

