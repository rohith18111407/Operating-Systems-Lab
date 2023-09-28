#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t ret_val;
    printf("\nThe process id is %d\n",getpid());
    return 0;
}