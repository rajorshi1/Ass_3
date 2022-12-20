#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void getCharArrays(int Index, char Buff[5][6], char arrstr[50][5]) {
    for (int i = Index; i < Index + 5; i++) {
        for (int j=0; j<6; j++) {
            if (j==5) Buff[i-Index][j] = i;
            else Buff[i-Index][j] = arrstr[i][j];
        }
    }
}

void printCharArray(char Buff[5][6])
{
    for (int i = 0; i < 5; i++) {
        for (int j=0; j<5; j++) {
            printf("%c", Buff[i][j]);
        }
        printf("\n");
    }
}

void randomStringGenerator(char arrstr[50][5]){
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            arrstr[i][j] = rand() % 26 + 65;
        }
    }
}

int main() {
    char arrstr[50][5] = {{0}};
    randomStringGenerator(arrstr);
    char Buff[5][6];
    mkfifo("fifoString", 0777);
    int receivedIndex = -1;
    struct timespec before;
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (int i=0; i<10; i++) {
        int fd = open("fifoString", O_WRONLY);
        getCharArrays(receivedIndex+1, Buff, arrstr);
        write(fd, Buff, sizeof(char) * 30);
        close(fd);
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
