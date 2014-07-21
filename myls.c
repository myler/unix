#include "apue.h"
#include <dirent.h>

int
main(int argc, char *argv[])
{
    DIR           *dp;
    struct dirent *dirp;
    const char *default_arg = "./";

    if(argc > 2)
        err_quit("usage: test directory_name");
    if (argc < 2) 
        if((dp = opendir(default_arg)) == NULL)
            err_sys("Can't open %s", default_arg);

    if((dp = opendir(argv[1])) == NULL)
        err_sys("Can't open %s", argv[1]);

    while((dirp = readdir(dp)) != NULL)
        printf("%s\t%d\t%u\n",
                dirp->d_name, dirp->d_reclen, dirp->d_type);

    closedir(dp);
    return 0;
}