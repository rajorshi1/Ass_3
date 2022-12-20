#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid>0)
    {
        execl("./P1","./P1",NULL);
    }
    else{
        execl("./P2","./P2",NULL);
    }
    return 0;
}
