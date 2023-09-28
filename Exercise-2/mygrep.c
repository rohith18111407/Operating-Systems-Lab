#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int fd,n;
    char buffer[1024];
    char *pattern=argv[1];
    char *filename=argv[2];
    off_t offset=0;

    fd=open(filename,O_RDONLY);

    while((n=read(fd,buffer,sizeof(buffer)))>0)
    {
        for(int i=0;i<n;i++)
        {
            if(buffer[i]=='\n')
            {
                if(strstr(buffer+offset,pattern)!=NULL)
                {
                    printf("%.*s\n",(int)(i-offset),buffer+offset);
                }
                offset=i+1;
            }
        }
        offset=n-offset;
        memmove(buffer,buffer+offset,offset);
    }
    close(fd);
    return 0;
}