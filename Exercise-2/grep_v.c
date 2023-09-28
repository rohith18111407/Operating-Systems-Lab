#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

void main(int argc,char *argv[])
{
    int fd;
    int bytes_read;
    char line[1024];
    char token[100][100];
    int count=0;
    int j=0;
    char *pattern;
    int pattern_length;
    int ln=1;
    int match=0;

    if(argc!=3)
    {
        printf("provide grep<pattern><file>\n");
    }

    pattern=argv[1];
    pattern_length=strlen(pattern);
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
        if(strstr(token[i],pattern)==NULL)
        {
            printf("%s\n",token[i]);
            match= 1;
        }
    }
    close(fd);
}