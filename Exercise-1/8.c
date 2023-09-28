#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

long factorial(int num)
{
    if(num==0)
        return 1;
    return (factorial(num-1)*num);
}

void series(int num)
{
    for(int i=0;i<=num;i++)
        printf("%d ",i);
}

int main(int argc,char *argv[])
{
    pid_t ret_val=fork();
    if(argc==3)
    {
        if(ret_val<0)
        {
            //fork has failed
            printf("\nFork failure\n");
        }
        else if(ret_val==0)
        {
            printf("\nChild Process\n");
            printf("The factorial of %d is %ld\n",atoi(argv[1]),factorial(atoi(argv[1])));
        }
        else
        {
            printf("\nParent process\n");
            series(atoi(argv[2]));
        }
    }
    else
    {
        printf("\nPlease pass 2 command line arguments\n");
    }
}