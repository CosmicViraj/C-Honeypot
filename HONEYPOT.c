#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")  
#define PORT 8080           
#define BUFFER_SIZE 1024    

void log_connection(struct sockaddr_in client) {
    FILE *logFile = fopen("honeypot_log.txt", "a");
    if (logFile == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }
    
    char *client_ip = inet_ntoa(client.sin_addr);  
    int client_port = ntohs(client.sin_port);

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';  

    fprintf(logFile, "Connection from %s:%d at %s\n", client_ip, client_port, timestamp);
    fclose(logFile);
}

int main() {
    WSADATA wsaData;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        return 1;
    }
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        perror("Binding failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        perror("Listening failed");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Honeypot is running on port %d. Waiting for connections...\n", PORT);
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            perror("Accepting connection failed");
            continue;
        }
        log_connection(address);
        const char *fake_response = "Welcome to the fake service!\n";
        send(new_socket, fake_response, strlen(fake_response), 0);
        closesocket(new_socket);
    }
    closesocket(server_fd);
    WSACleanup();

    return 0;
}

