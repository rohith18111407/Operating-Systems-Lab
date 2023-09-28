#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct dirent *dp;
    DIR *dir;
    struct stat fileStat;
    struct passwd *pw;
    struct group *gr;
    char dateTime[80];

    if(argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    if((dir = opendir(argv[1])) == NULL) {
        perror("opendir error");
        exit(1);
    }

    while((dp = readdir(dir)) != NULL) {
        char path[1024];
        sprintf(path, "%s/%s", argv[1], dp->d_name);

        if(stat(path, &fileStat) < 0) {
            perror("stat error");
            exit(1);
        }

        pw = getpwuid(fileStat.st_uid);
        gr = getgrgid(fileStat.st_gid);

        strftime(dateTime, 80, "%b %d %H:%M", localtime(&fileStat.st_mtime));

        printf("%s %ld %s %s %ld %s %s\n",
               (S_ISDIR(fileStat.st_mode)) ? "d" : "-",
               (long) fileStat.st_nlink,
               (pw == NULL) ? "" : pw->pw_name,
               (gr == NULL) ? "" : gr->gr_name,
               (long) fileStat.st_size,
               dateTime,
               dp->d_name);
    }

    closedir(dir);
    exit(0);
}
