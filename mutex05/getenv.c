#include <stdlib.h>
#include <stdio.h>

int main(void) {
	char *s;

	s = getenv("PATH");
	printf("PATH = %s\n", s);

	return 0;
}