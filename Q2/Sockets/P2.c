#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

void printCharArray(char buff[5][6]){
    printf("The strings received from P1: \n");
    for (int i = 0; i < 5; i++) {
        for (int j=0; j<5; j++) {
            printf("%c", buff[i][j]);
        }
        printf(" ");
    }
    printf("\n");
    printf("Max Index Received from P1: %d\n", buff[4][5]);
}

int main(int argc, char const *argv[])
{
    int Index;
    int sock;
    struct sockaddr_un server;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("opening stream socket");
        exit(1);
    }
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, "/tmp/sock");
    if (connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) < 0)
    {
        close(sock);
        perror("connecting stream socket");
        exit(1);
    }
    char buff[5][6];
    for (int i=0; i<10; i++) {
        read(sock,(void*)&buff,sizeof(char)*30);
        printCharArray(buff);
        Index = buff[4][5];
        write(sock,&Index,sizeof(int));
    }
    close(sock);
    return (0);
}
