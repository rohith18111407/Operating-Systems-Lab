//Raghul code 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    char *pattern = argv[1];
    char *filename = argv[2];
    int file = open(filename, O_RDONLY);
    char buffer[1024];
    int n;

    while ((n = read(file, buffer, 1024)) > 0) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (buffer[i] == '\n') 
            {
                buffer[i] = '\0';
                if (!strstr(buffer, pattern)) 
                {
                    printf("%s\n", buffer);
                }
                buffer[i] = '\n';
            }
        }
    }
    printf("%s", buffer);
    close(file);
    return 0;
}
