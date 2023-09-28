#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

void main(int argc,char *argv[])
{
    int fd;
    int bytes_read;
    char line[1024];
    char token[100][100];
    int count=0;
    int j=0;
    char *pattern;
    int ln=1;

    if(argc!=3)
    {
        printf("provide grep<pattern><file>\n");
    }

    pattern=argv[1];
    fd=open(argv[2],O_RDONLY);

    if(fd==-1)
    {
        printf("errror loading the file");
    }
    while((bytes_read=read(fd,line,1024))>0)
    {
        for(int i=0;i!=bytes_read;i++)
        {
            if(line[i]=='\n')
            {
                ln++;
                j++;
                count=0;
            }
            else
            {
                token[j][count++]=line[i];
            }
        }
    }
    for(int i=0;i!=ln;i++)
    {
        if(strstr(token[i],pattern)!=NULL)
        {
            printf("%s\n",token[i]);
        }
    }
    close(fd);
}