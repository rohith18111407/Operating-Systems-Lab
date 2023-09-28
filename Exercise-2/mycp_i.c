#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    int source_fd, dest_fd, read_size;
    char buffer[BUFFER_SIZE];
    struct stat statbuf;

    if (argc != 3) {
        printf("Usage: mycp-i source_file dest_file\n");
        exit(EXIT_FAILURE);
    }

    // Check if destination file already exists and prompt for confirmation
    if (access(argv[2], F_OK) == 0) {
        printf("The file %s already exists. Do you want to overwrite it? (y/n) ", argv[2]);
        char response;
        scanf("%c", &response);
        if (response != 'y' && response != 'Y') {
            exit(EXIT_SUCCESS);
        }
    }

    // Open source file for reading
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Get file status to determine permissions of source file
    if (fstat(source_fd, &statbuf) == -1) {
        perror("Error getting source file status");
        exit(EXIT_FAILURE);
    }

    // Open destination file for writing
    dest_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, statbuf.st_mode);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    // Copy contents of source file to destination file
    while ((read_size = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, read_size) != read_size) {
            perror("Error writing to destination file");
            exit(EXIT_FAILURE);
        }
    }
    if (read_size == -1) {
        perror("Error reading from source file");
        exit(EXIT_FAILURE);
    }

    // Close file descriptors
    close(source_fd);
    close(dest_fd);

    return 0;
}
