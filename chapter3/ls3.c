//
// Created by 王琛超 on 2020/2/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>



void do_ls(char *name);
void do_stat(char *name);
void show_stat_info(char *name, struct stat *stat_ptr);
void mode_to_letters(struct stat *, char *);

char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        do_ls(".");
    } else {
        printf("ls1 open the file %s:\n", *++argv);
        do_ls(*argv);
    }
    return 0;
}

void do_ls(char *name) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    if ((dir_ptr = opendir(name)) == NULL) {
        perror(name);
        exit(EXIT_FAILURE);
    }

    if ((chdir(name)) == -1) {
        perror(name);
        exit(EXIT_FAILURE);
    }

    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        do_stat(dirent_ptr->d_name);
    }
    closedir(dir_ptr);
}

void do_stat(char *name) {
    struct stat stat_ptr;
    if (stat(name, &stat_ptr) != -1) {
        show_stat_info(name, &stat_ptr);
    } else {
        perror(name);
        exit(EXIT_FAILURE);
    }
}

void show_stat_info(char *name, struct stat *stat_ptr) {
    char letters[11];
    mode_to_letters(stat_ptr, letters);

    printf("%s ", letters);
    printf("%ld ", stat_ptr->st_nlink);
    char *u_name = uid_to_name(stat_ptr->st_uid);
    printf("%-10s ", u_name);
    char *g_name = gid_to_name(stat_ptr->st_gid);
    printf("%-10s ", g_name);
    printf("%ld ", stat_ptr->st_size);

    char *time_str = ctime(&(stat_ptr->st_mtime)) + 4;
    printf("%.12s ", time_str);

    printf("%s ", stat_ptr->st_ino);

    printf("%s ", name);
    printf("\n");

}

void mode_to_letters(struct stat *stat_ptr, char *letters) {
    strcpy(letters, "----------");
    int mode = stat_ptr->st_mode;
    if (S_ISREG(mode)) letters[0] = '-';
    if (S_ISDIR(mode)) letters[0] = 'd';
    if (S_ISLNK(mode)) letters[0] = 'l';
    if (S_ISCHR(mode)) letters[0] = 'c';
    if (S_ISBLK(mode)) letters[0] = 'b';

    if (mode & S_IRUSR) letters[1] = 'r';
    if (mode & S_IWUSR) letters[2] = 'w';
    if (mode & S_IXUSR) letters[3] = 'x';

    if (mode & S_IRGRP) letters[4] = 'r';
    if (mode & S_IWGRP) letters[5] = 'w';
    if (mode & S_IXGRP) letters[6] = 'x';

    if (mode & S_IROTH) letters[7] = 'r';
    if (mode & S_IWOTH) letters[8] = 'w';
    if (mode & S_IXOTH) letters[9] = 'x';
}

char *uid_to_name(uid_t uid) {
    struct passwd *pwd;
    static char str[10];
    if ((pwd = getpwuid(uid)) == NULL) {
        sprintf(str, "%d", uid);
        return str;
    } else {
        return pwd->pw_name;
    }
}

char *gid_to_name(gid_t gid) {
    struct group *grp;
    static char str[10];
    if ((grp = getgrgid(gid)) == NULL) {
        sprintf(str, "%d", gid);
        return str;
    } else {
        return grp->gr_name;
    }
}
