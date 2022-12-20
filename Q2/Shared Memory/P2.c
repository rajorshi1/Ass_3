#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/shm.h>

void printArraydet(char array[]) {
    printf("Max Index Received by P1: %d\n",array[5]);
    printf("String received by P1:");
    for(int j = 0 ; j < 5; j++){
        printf("%c",array[j]);
    }
    printf("\n");
}

int main(){
    sleep(2);
    char buff[5][6];
    int mem = shmget(6969,100,IPC_CREAT | 0666);
    char *ptr = (char *)shmat(mem,NULL,0);
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            strcpy(buff[j],ptr);
            sleep(1);
        }
        printArraydet(buff[4]);
        strcpy(ptr,buff[4]);
        sleep(1);
    }
    printf("All strings received \n");
}
