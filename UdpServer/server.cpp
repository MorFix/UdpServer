#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    8181
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char* hello = "Hello from server";
    struct sockaddr_in serveraddr, clientaddr;

    // SOCK_DGRAM means UDP.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    
    // Filling server information
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len = sizeof(clientaddr), messageLength;
    
    // Looping for messages
    while (true) {
        memset(&clientaddr, 0, sizeof(clientaddr));
        memset(buffer, 0, MAXLINE);
        
        messageLength = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*)&clientaddr, (socklen_t*)&len);
        buffer[messageLength] = '\0';

        char* username = new char[MAXLINE / 2];
        char* password = new char[MAXLINE / 2];

        int index = 0;
        char currChar = buffer[0];

        while (currChar != '~' && currChar != '\0') {
            strncat(username, &currChar, sizeof(char));
            currChar = buffer[++index];
        }

        currChar = buffer[++index];
        while (currChar != '\0') {
            strncat(password, &currChar, sizeof(char));
            currChar = buffer[++index];
        }
        
        const char* response = strcmp(username, "mor") == 0 && strcmp(password, "cohen") == 0 ? "OK!" : "WRONG!";

        std::cout << response << "\n";
        sendto(sockfd, response, strlen(response), MAXLINE, (const struct sockaddr*)&clientaddr, len);
    }
    
    return 0;
}