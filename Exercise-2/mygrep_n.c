//Raghul code 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
    char* search_string = argv[1];
    char* file_name = argv[2];
    int file = open(file_name, O_RDONLY);
    char buffer[1024];
    ssize_t bytes_read;
    int line_number = 1;

    while ((bytes_read = read(file, buffer, 1024)) > 0) 
    {
        char* newline = strchr(buffer, '\n');
        while (newline != NULL) 
        {
            *newline = '\0';
            if (strstr(buffer, search_string) != NULL) 
            {
                printf("%d: %s\n", line_number, buffer);
            }
            line_number++;
            buffer[1024 - 1] = '\0';
            newline = strchr(newline + 1, '\n');
        }
    }
    close(file);
    return 0;
}
