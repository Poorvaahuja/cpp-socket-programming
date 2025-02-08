#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000  // Change if necessary

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert address (use "127.0.0.1" if running on local machine)
    if (inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // Send message
    char *message = "Hello from Client!";
    send(sock, message, strlen(message), 0);

    // Receive response
    read(sock, buffer, 1024);
    printf("Server: %s\n", buffer);

    // Close connection
    close(sock);
    return 0;
}
