#include <stdio.h>
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
        read(fd, &destArr, sizeof(char)*30);
        close(fd);
        printCharArray(destArr);
        int temp = destArr[4][5];
        fd = open("fifoString", O_WRONLY);
        write(fd, &temp, sizeof(int));
        close(fd);
    }
    return 0;
}
