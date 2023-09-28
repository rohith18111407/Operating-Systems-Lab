#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    struct dirent *dp;
    DIR *dir;

    if(argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    if((dir = opendir(argv[1])) == NULL) {
        perror("opendir error");
        exit(1);
    }

    while((dp = readdir(dir)) != NULL) {
        printf("%s\n", dp->d_name);
    }

    closedir(dir);
    exit(0);
}
