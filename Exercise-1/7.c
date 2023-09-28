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
    wait(NULL); //wait for the child process to complete
    return 0;
}