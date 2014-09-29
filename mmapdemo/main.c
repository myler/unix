#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR (1024*1024*1024)

int main(int argc, char* argv[]) {
    int fin, fout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if (argc != 3)
        err_quit("Usage: %s <src-file> <dst-file>", argv[0]);

    if ((fin = open(argv[1], O_RDONLY)) < 0)
        err_sys("can't open %s for reading", argv[1]);

    if ((fout = open(argv[2],
                     O_RDWR | O_CREAT | O_TRUNC,
                     FILE_MODE)) < 0)
        err_sys("can't create %s for writing", argv[2]);

    if (fstat(fin, &sbuf) < 0)
        err_sys("fstat error");

    if (ftruncate(fout, sbuf.st_size) < 0)
        err_sys("ftruncate error");

    while (fsz < sbuf.st_size) {
        if ((sbuf.st_size - fsz) > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_size - fsz;

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED,
                        fin, fsz)) == MAP_FAILED)
            err_sys("mmap error for input");

        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE,
                        MAP_SHARED, fout, fsz)) == MAP_FAILED)
            err_sys("mmap error for output");

        memcpy(dst, src, copysz);
        msync(dst, copysz, MS_SYNC);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }
    exit(0);
}

