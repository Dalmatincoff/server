#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol){
    int res = socket(domain, type, protocol);
    if(res == -1){
        perror("failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = bind(sockfd, addr, addrlen);
    if(res == -1) {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog){
    int res = listen(sockfd, backlog);
    if(res == -1) {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int res = accept(sockfd, addr, addrlen);
    if(res == -1) {
        perror("failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

int main(){
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(iport);
    Bind(server,(struct sockaddr *) &adr, sizeof(adr));
    Listen(server, 5);
    socklen_t adrlen = sizeof(adr);
    int fd = Accept(server,(struct sockaddr *) &adr, &adrlen);
    ssize_t nread;
    char buf[256];
    char s[256];
    nread = read(fd, buf, 256);
    if(nread == -1){
        perror("failed");
        exit(EXIT_FAILURE);
    }
    if(nread == 0){
        printf("END if FILE occured");
    }
    FILE *f = fopen(read(fd, s, 256), "a");
    fwrite(buf, sizeof (char), strlen(buf), f);
    sleep(1);
    fclose(f);
    close(fd);
    close(server);
    return 0;
}
