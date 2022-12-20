#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define NAME "/tmp/sock"

void getCharArrays(int Index, char toBeSent[5][6], char stringArray[50][5]) {
    for (int i = Index; i < Index + 5; i++) {
        for (int j=0; j<6; j++) {
            if (j==5) toBeSent[i-Index][j] = i;
            else toBeSent[i-Index][j] = stringArray[i][j];
        }
    }
}

void printCharArray(char toBeSent[5][5])
{
    for (int i = 0; i < 5; i++) {
        for (int j=0; j<5; j++) {
            printf("%c", toBeSent[i][j]);
        }
        printf("\n");
    }
}

void randomStringGenerator(char stringArray[50][5])
{
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            stringArray[i][j] = rand() % 26 + 65;
        }
    }
}

int main(int argc, char const *argv[])
{
    char stringArray[50][5] = {{0}};
    randomStringGenerator(stringArray);
    char toBeSent[5][6];
    int sock, msgsock;
    struct sockaddr_un server;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Socket making failed\n");
        exit(1);
    }
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, NAME);
    if (bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un)))
    {
        perror("binding stream socket");
        unlink(NAME);
        exit(1);
    }
    int option = 1;
    int receivedIndex = -1;
    listen(sock, 5);
    msgsock = accept(sock, 0, 0);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (msgsock == -1)
        printf("Socket error\n");
    else {
        struct timespec before;
        struct timespec after;
        clock_gettime(CLOCK_MONOTONIC, &before);
        for (int i=0; i<10; i++) {
            getCharArrays(receivedIndex + 1, toBeSent, stringArray);
            write(msgsock, (void *)&toBeSent, sizeof(char)*30);
            read(msgsock,&receivedIndex,sizeof(int));
            printf("The recieved index from P2 is %d\n",receivedIndex);
        }
        clock_gettime(CLOCK_MONOTONIC, &after);
        unsigned long time1 = (before.tv_sec * 1000000000) + before.tv_nsec;
        unsigned long time2 = (after.tv_sec * 1000000000) + after.tv_nsec;
        float time_taken = ((float)(time2 - time1))/1000000000;
        printf("Time taken to acknowledge all strings: %f\n", time_taken);
    }
    close(msgsock);
    unlink(NAME);
    close(sock);
    return (0);
}
