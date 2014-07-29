#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int    myftw(char *, Myfunc *);
static int    dopath(Myfunc *);
static long   nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int
main(int argc, char *argv[])
{
  int ret;

  if (argc != 2)
    err_quit("Usage: %s <starting-pathname>", argv[0]);

  ret = myftw(argv[1], myfunc);
  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if (ntot == 0)
    ntot = 1;

  printf("************************************\n");
  printf("*         File statistics          *\n");
  printf("************************************\n");
  printf("* regular files = %7ld, %5.2f %% *\n", nreg, (double)nreg * 100 / ntot);
  printf("* directories   = %7ld, %5.2f %% *\n", ndir, (double)ndir * 100 / ntot);
  printf("* block special = %7ld, %5.2f %% *\n", nblk, (double)nblk * 100 / ntot);
  printf("* char special  = %7ld, %5.2f %% *\n", nchr, (double)nchr * 100 / ntot);
  printf("* FIFOs         = %7ld, %5.2f %% *\n", nfifo, (double)nfifo * 100 / ntot);
  printf("* symblic links = %7ld, %5.2f %% *\n", nslink, (double)nslink * 100 / ntot);
  printf("* sockets       = %7ld, %5.2f %% *\n", nsock, (double)nsock * 100 / ntot);
  printf("*                   Total: %7ld *\n", ntot);
  printf("************************************\n");

  exit(ret);
}

#define FTW_F   1
#define FTW_D   2
#define FTW_DNR 3
#define FTW_NS  4

static char *fullpath;
//static size_t pathlen;
static size_t pathlen = PATH_MAX;

static int
myftw(char *pathname, Myfunc *func)
{
//  fullpath = path_alloc(&pathlen);

//  if (pathlen <= strlen(pathname))
//    {
//      pathlen = strlen(pathname) * 2;
//      if ((fullpath = realloc(fullpath, pathlen)) == NULL)
//        err_sys("realloc failed");
//    }
  if ((fullpath = realloc(fullpath, pathlen)) == NULL)
    err_sys("realloc failed");
  strcpy(fullpath, pathname);
  return (dopath(func));
}

static int
dopath(Myfunc *func)
{
  struct stat   stat_buf;
  struct dirent *dirp;
  DIR           *dp;
  int           ret, n;

  if (lstat(fullpath, &stat_buf) < 0)
    return (func(fullpath, &stat_buf, FTW_NS));
  if (S_ISDIR(stat_buf.st_mode) == 0)
    return (func(fullpath, &stat_buf, FTW_F));
  if ((ret = func(fullpath, &stat_buf, FTW_D)) != 0)
    return (ret);
  n = strlen(fullpath);
//  if (n + NAME_MAX + 2 > pathlen)
//    {
//      pathlen *= 2;
//      if ((fullpath = realloc(fullpath, pathlen)) == NULL)
//        err_sys("realloc failed");
//    }
  fullpath[n++] = '/';
  fullpath[n] = 0;
  if ((dp = opendir(fullpath)) == NULL)
    return (func(fullpath, &stat_buf, FTW_DNR));
  while ((dirp = readdir(dp)) != NULL)
    {
      if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
        continue;
      strcpy(&fullpath[n], dirp->d_name);
      if ((ret = dopath(func)) != 0)
        break;
    }
  fullpath[n - 1] = 0;
  if (closedir(dp) < 0)
    err_ret("can't close directory %s", fullpath);
  return (ret);
}

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
  switch (type) {
    case FTW_F:
      switch (statptr->st_mode & S_IFMT) {
        case S_IFREG:
          nreg++;
          break;
        case S_IFBLK:
          nblk++;
          break;
        case S_IFCHR:
          nchr++;
          break;
        case S_IFIFO:
          nfifo++;
          break;
        case S_IFLNK:
          nslink++;
          break;
        case S_IFSOCK:
          nsock++;
          break;
        case S_IFDIR:
          err_dump("for S_IFDIR for %s", pathname);
        default:
          break;
        }
      break;
    case FTW_D:
      ndir++;
      break;
    case FTW_DNR:
      err_ret("can't read directory %s", pathname);
      break;
    case FTW_NS:
      err_ret("stat error for %s", pathname);
      break;
    default:
      err_dump("unknown type %d for pathname %s", type, pathname);
    }
  return (0);
}
