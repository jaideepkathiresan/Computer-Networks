#include <stdio.h>
#include <arpa/inet.h>

void classfulAddressing(const char *ipAddress) {
    struct in_addr addr;
    
    if (inet_pton(AF_INET, ipAddress, &addr) <= 0) {
        printf("Invalid IP address\n");
        return;
    }

    unsigned int ip = ntohl(addr.s_addr);

    if ((ip & 0x80000000) == 0) {
        // Class A Address
        unsigned int firstAddress = (ip & 0xFF000000) | 0x00000000;
        unsigned int lastAddress = (ip & 0xFF000000) | 0x00FFFFFF;
        unsigned int numHosts = 0x00FFFFFF;
        
        printf("Classful addressing - Class A\n");
        printf("First address: %d.%d.%d.%d\n", (firstAddress >> 24) & 0xFF, (firstAddress >> 16) & 0xFF, (firstAddress >> 8) & 0xFF, firstAddress & 0xFF);
        printf("Last address: %d.%d.%d.%d\n", (lastAddress >> 24) & 0xFF, (lastAddress >> 16) & 0xFF, (lastAddress >> 8) & 0xFF, lastAddress & 0xFF);
        printf("Number of hosts: %u\n", numHosts);
    } else if ((ip & 0xC0000000) == 0x80000000) {
        // Class B Address
        unsigned int firstAddress = (ip & 0xFFFF0000) | 0x0000;
        unsigned int lastAddress = (ip & 0xFFFF0000) | 0xFFFF;
        unsigned int numHosts = 0xFFFF - 1;
        
        printf("Classful addressing - Class B\n");
        printf("First address: %d.%d.%d.%d\n", (firstAddress >> 24) & 0xFF, (firstAddress >> 16) & 0xFF, (firstAddress >> 8) & 0xFF, firstAddress & 0xFF);
        printf("Last address: %d.%d.%d.%d\n", (lastAddress >> 24) & 0xFF, (lastAddress >> 16) & 0xFF, (lastAddress >> 8) & 0xFF, lastAddress & 0xFF);
        printf("Number of hosts: %u\n", numHosts);
    } else if ((ip & 0xE0000000) == 0xC0000000) {
        // Class C Address
        unsigned int firstAddress = (ip & 0xFFFFFF00) | 0x00;
        unsigned int lastAddress = (ip & 0xFFFFFF00) | 0xFF;
        unsigned int numHosts = 0xFF - 1;
        
        printf("Classful addressing - Class C\n");
        printf("First address: %d.%d.%d.%d\n", (firstAddress >> 24) & 0xFF, (firstAddress >> 16) & 0xFF, (firstAddress >> 8) & 0xFF, firstAddress & 0xFF);
        printf("Last address: %d.%d.%d.%d\n", (lastAddress >> 24) & 0xFF, (lastAddress >> 16) & 0xFF, (lastAddress >> 8) & 0xFF, lastAddress & 0xFF);
        printf("Number of hosts: %u\n", numHosts);
    } else {
        printf("IP address does not belong to Class A, B, or C\n");
    }
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

    printf("Network address: %d.%d.%d.%d\n", (networkAddress >> 24) & 0xFF, (networkAddress >> 16) & 0xFF, (networkAddress >> 8) & 0xFF, networkAddress & 0xFF);
    printf("Final address: %d.%d.%d.%d\n", (broadcastAddress >> 24) & 0xFF, (broadcastAddress >> 16) & 0xFF, (broadcastAddress >> 8) & 0xFF, broadcastAddress & 0xFF);
    printf(" Number of hosts: %u\n", numHosts);
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

