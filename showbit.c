	#include <string.h>
	#include <malloc.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <memory.h>

	typedef struct AA {
		int a1:5;
		int a2:2;
	} AA;

	int main() {
		AA aa;
		char cc[100];
		strcpy(cc, "0123456789");
		memcpy(&aa, cc, sizeof(AA));
		printf("%d\n", aa.a1);
		printf("%d\n", aa.a2);
		return 0;
	}