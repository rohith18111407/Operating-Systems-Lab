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

    int res=wait(NULL); //wait for the child to die
    if(res==-1)
    {
        printf("No children to wait...\n");
    }    
    else
    {
        printf("%d finished execution\n",res);
    }
}