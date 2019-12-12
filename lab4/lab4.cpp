#include <unistd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>

void getRWX(const unsigned short m);

void printdir(char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(dir)) == NULL) {
        printf("fail to open the dir\n");
        return;
    }
    chdir(dir);
    while ((entry = readdir(dp)) != NULL) {
      lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
               	continue;
            getRWX(statbuf.st_mode);
            printf("%d   ", depth);
            struct passwd *pwd;
            pwd = getpwuid(statbuf.st_uid);
            printf("%s   ", pwd->pw_name);

            struct passwd *gpwd;
            if((gpwd = getpwuid(statbuf.st_gid))!=NULL) {
            	printf("%s\t",gpwd->pw_name);
            }
            printf("%ld\t",statbuf.st_size);

            printf("%s\t",strtok(ctime(&statbuf.st_mtime),"\n"));
            printf("%s\n",entry->d_name);
            printdir(entry->d_name,depth+1);
        } else {
            getRWX(statbuf.st_mode);
            printf("%d   ",depth); 
            struct passwd *pwd;
            pwd = getpwuid(statbuf.st_uid);
            printf("%s   ",pwd->pw_name);
            struct passwd *gpwd;
            if((gpwd = getpwuid(statbuf.st_gid))!=NULL) {
      	       printf("%s\t",gpwd->pw_name);
            }
            printf("%ld\t",statbuf.st_size);
            printf("%s\t",strtok(ctime(&statbuf.st_ctime)+4, "\n"));
            printf("%s\n",entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}


void getRWX(const unsigned short m)
{
    if (m& S_IRUSR)
       printf("r");
   else
       printf("-");

    if (m & S_IWUSR)
         printf("w");
    else
        printf("-");

    if (m & S_IXUSR)
         printf("x");
    else
        printf("-");

    if (m & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (m & S_IWGRP)
         printf("w");
    else
        printf("-");

    if (m & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (m & S_IROTH)
        printf("r");
    else
        printf("-");

    if (m & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (m & S_IXOTH)
        printf("x   ");
    else
        printf("-   ");
        return;
}

int main(){
    char dirr[50];
	printf("please input the dir name\n");
	scanf("%s",dirr);
	printdir(dirr,1);
	return 0;
}
 
