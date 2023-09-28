#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void listdir(const char *path, int indent) {
    struct dirent *dp;
    DIR *dir;
    struct stat fileStat;
    struct passwd *pw;
    struct group *gr;
    char dateTime[80];
    char newPath[1024];

    if((dir = opendir(path)) == NULL) {
        perror("opendir error");
        exit(1);
    }

    while((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        printf("%*s%s\n", indent, "", dp->d_name);

        sprintf(newPath, "%s/%s", path, dp->d_name);

        if(stat(newPath, &fileStat) < 0) {
            perror("stat error");
            exit(1);
        }

        if (S_ISDIR(fileStat.st_mode)) {
            listdir(newPath, indent + 4);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    listdir(argv[1], 0);

    exit(0);
}
