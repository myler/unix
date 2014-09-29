#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 1024

int main(void)
{
    char result_buf[MAXLINE];
    char command[MAXLINE];
    int rc = 0;
    FILE *fp;

    snprintf(command, sizeof(command), "ls ./ | wc -l");

    if ((fp = popen(command, "r")) == NULL)
        perror("popen error\n"), exit(1);

    while (fgets(result_buf, sizeof(result_buf), fp) != NULL) {
        if (result_buf[strlen(result_buf) - 1] == '\n')
            result_buf[strlen(result_buf) - 1] = '\0';
        printf("command: [%s], result: %s\n", command, result_buf);
    }

    if ((rc = pclose(fp)) < 0)
        perror("pclose error\n"), exit(1);
    else
        printf("command: [%s], exit_state: %d, return value: %d\n",
               command, rc, WEXITSTATUS(rc));
    return 0;
}

