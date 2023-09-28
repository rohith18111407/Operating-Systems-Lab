#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int id=fork();
    if(id==0)
    {
        sleep(10);
    }
    printf("Current ID: %d  Parent ID: %d\n",getpid(),getppid());
    return 0;
}