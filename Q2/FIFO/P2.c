#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void printCharArray(char toBeSent[5][6]){
    printf("The strings received from P1: \n");
    for (int i = 0; i < 5; i++) {
        for (int j=0; j<5; j++) {
            printf("%c",toBeSent[i][j]);
        }
        printf(" ");
    }
    printf("\n");
    printf("Max Index received from P1: %d\n", toBeSent[4][5]);
}

int main()
{
    char destArr[5][6];
    for (int i=0; i<10; i++) {
        int fd = open("fifoString", O_RDONLY);
        if (!fd) {
            perror("Couldn't Open\n");
            exit(1);
        }
        int z = read(fd, &destArr, sizeof(char)*30);
        if (!z) {
            perror("Couldn't Read\n");
            exit(1);
        }
        close(fd);
        printCharArray(destArr);
        int temp = destArr[4][5];
        fd = open("fifoString", O_WRONLY);
        if (!fd) {
            perror("Couldn't Open\n");
            exit(1);
        }
        int y = write(fd, &temp, sizeof(int));
        if (!y) {
            perror("Couldn't Write\n");
            exit(1);
        }
        close(fd);
    }
    return 0;
}
