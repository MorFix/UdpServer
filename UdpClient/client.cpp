#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8181
#define MAXLINE 1024

using namespace std;

// Driver code
int main() {
    int sockfd, reslen;
    char* username = new char[MAXLINE / 2];
    char* password = new char[MAXLINE / 2];
    char message[MAXLINE];
    char response[MAXLINE];

    struct sockaddr_in servaddr; 

    // SOCK_DGRAM means UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(message, 0, MAXLINE);
        
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    cout << "Please enter username:\n";
    cin >> username;

    strncat(message, username, sizeof(char) * MAXLINE / 2);
    strcat(message, "~");

    cout << "Please enter password:\n";
    cin >> password;
    strncat(message, password, sizeof(char) * MAXLINE / 2);

    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    recvfrom(sockfd, response, MAXLINE, MSG_WAITALL, (struct sockaddr*)&servaddr, (socklen_t*)&reslen);
    
    cout << response << "\n";

    close(sockfd);

    return 0;
}