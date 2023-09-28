#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int source,dest,fp;

    char buffer[2000];
    source=open(argv[1],O_RDONLY);
    dest=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    while((fp=read(source,buffer,sizeof(buffer)))>0)
    {
        if(write(dest,buffer,fp)!=fp)
        {
            printf("Error writing to file %s\n",argv[2]);
            exit(1);
        }
        else
        {
            printf("Content copied\n");
        }
    }
    close(source);
    close(dest);
    return 0;
}
