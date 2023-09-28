#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t ret_val;
    printf("\nThe process id is %d\n",getpid());

    ret_val=fork();
    if(ret_val<0)
    {
        //fork has failed
        printf("\nFork failure\n");
    }
    else if(ret_val==0)
    {
        //child process
        printf("\nChild Process\n");
        printf("The process id is %d\n",getpid());
        sleep(20);
    }
    else
    {
        //parent process
        wait();
        printf("Parent Process\n");
        printf("The process id is %d\n",getpid());
        sleep(30);
    }
    return 0;
}