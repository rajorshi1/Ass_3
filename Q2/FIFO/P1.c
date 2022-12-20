#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void getCharArrays(int Index, char toBeSent[5][5], char stringArray[50][5], int indexArr[])
{
    for (int i = Index; i < Index + 5; i++)
    {
        for (int j=0; j<5; j++) {
            toBeSent[i-Index][j] = stringArray[i][j];
        }
        indexArr[i-Index] = i;
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
int main() {

    char stringArray[50][5] = {{0}};
    randomStringGenerator(stringArray);
    char toBeSent[5][5];
    int indexArr[5];
    mkfifo("fifoString", 0777);
    mkfifo("fifoIndex", 0777);
    int receivedIndex = -1;
    struct timespec before;
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (int i=0; i<10; i++) {
        int fd = open("fifoString", O_WRONLY);
        getCharArrays(receivedIndex+1, toBeSent, stringArray, indexArr);
        write(fd, toBeSent, sizeof(char) * 25);
        close(fd);
        int fd2 = open("fifoIndex", O_WRONLY);
        write(fd2, indexArr, sizeof(int) * 5);
        close(fd2);
        fd = open("fifoString", O_RDONLY);
        read(fd, &receivedIndex, sizeof(int));
        printf("Received Index %d from P2\n", receivedIndex);
        close(fd);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    unsigned long time1 = (before.tv_sec * 1000000000) + before.tv_nsec;
    unsigned long time2 = (after.tv_sec * 1000000000) + after.tv_nsec;
    float time_taken = ((float)(time2 - time1))/1000000000;
    printf("Time taken to acknowledge all strings: %f\n", time_taken);
    return 0;
}
