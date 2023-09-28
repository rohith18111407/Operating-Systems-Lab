#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char *argv[])
{
    char *search_string=argv[1];
    char *file_name=argv[2];

    int file=open(file_name,O_RDONLY);

    char buffer[1024];
    ssize_t bytes_read;
    int count=0;

    while((bytes_read=read(file,buffer,sizeof(buffer)))>0)
    {
        char *match=strstr(buffer,search_string);
        while(match!=NULL)
        {
            count++;
            match=strstr(match+1,search_string);
        }
    }
    printf("%d\n",count);
    close(file);
    return 0;
}