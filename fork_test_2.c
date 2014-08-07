#include <stdio.h>

int
main(void)
{
	fork();
	fork() && fork() || fork();
	fork();
	printf("+\n");
}
