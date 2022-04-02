#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = connect(sockfd, addr, addrlen);
    if( res == -1){
        perror("failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst){
    int res = inet_pton(af, srs, dst );
    if(res == 0){
        printf("failed: src doesnt contain a character"
               "string representing a valid network address in the specified"
               "addres family\n");
        exit(EXIT_FAILURE);
    }
    if(res == -1){
        perror("failed");
        exit(EXIT_FAILURE);
    }
}
int main(){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    char *port;
    printf("Port:\n");
    scanf("%s", port);
    int iport = atoi(port);
    adr.sin_port = htons(iport);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr*) &adr, sizeof(adr));
    char buf[256];
    ssize_t nread;
    nread = read(fd, buf, 256);
    if(nread == -1){
        perror("failed");
        exit(EXIT_FAILURE);
    }
    if(nread == 0) {
        printf("EOF occured\n");
    }
    char *s;
    printf("Enter filename\n");
    scanf("%s", s);
    FILE *f = fopen(s, "r");
    while (!feof(f)){
        fgets(buf, 256, f);
        write(STDOUT_FILENO, buf, nread);
    }
    fclose(f);
    close(fd);
    return 0;
}