#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

void main(int argc,char *argv[])
{
    int fd;
    char line[1024];
    char *pattern;
    int match=0;
    int ln=0;
    int bytes=0;
    int count=0;
    int j=0;
    char token[100][100];

    if(argc!=3)
    {
        printf("use grep<pattern><file>");
    }

    pattern=argv[1];
    fd=open(argv[2],O_RDONLY);

    if(fd==-1)
    {
        printf("error while opening the file");
    }

    while((bytes=read(fd,line,1024))>0)
    {
        for(int i=0;i!=bytes;i++)
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
            printf("%d:%s\n",i,token[i]);
        }
    }
    close(fd);
}