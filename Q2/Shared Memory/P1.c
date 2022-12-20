#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>

void getCharArrays(int Index, char toBeSent[5][6], char stringArray[50][5]) {
    for (int i = Index; i < Index + 5; i++) {
        for (int j=0; j<6; j++) {
            if (j==5) toBeSent[i-Index][j] = i;
            else toBeSent[i-Index][j] = stringArray[i][j];
        }
    }
}

void printArraydet(char array[6]) {
    printf("Max index received from P2: %d ",array[5]);
    for(int j = 0 ; j < 5; j++){
        printf("%c",array[j]);
    }
    printf("\n");
}

void randomStringGenerator(char stringArray[50][5]) {
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            stringArray[i][j] = rand() % 26 + 65;
        }
    }
}

int main() {
    sleep(1);
    char buff[6];
    char arrstr[50][5];
    randomStringGenerator(arrstr);
    char toBeSent[5][6];
    int receivedIndex = -1;
    int mem = shmget(6969,100,IPC_CREAT | 0666);
    char *ptr = (char *)shmat(mem,NULL,0);
    for (int i=0; i<10; i++) {
        getCharArrays(receivedIndex+1, toBeSent, arrstr);
        for(int j = 0 ; j < 5 ; j++){
            strcpy(ptr,toBeSent[j]);
            sleep(1);
        }
        strcpy(buff,ptr);
        sleep(1);
        printArraydet(buff);
        receivedIndex = buff[5];
    }
    printf("Transfer Complete \n");
}
