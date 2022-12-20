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

int main(){
    sleep(2);
    char buff[5][6];
    int mem = shmget(9999,100,IPC_CREAT | 0666);
    char *ptr = (char *)shmat(mem,NULL,0);
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            strcpy(buff[j],ptr);
            sleep(1);
        }
        printf("Max index received from P1: %d\n",buff[4][5]);
        printf("String:");
        for(int j = 0 ; j < 5; j++){
            printf("%c",buff[4][j]);
        }
        printf("\n");
        strcpy(ptr,buff[4]);
        sleep(1);
    }
    printf("All strings received \n");
}
