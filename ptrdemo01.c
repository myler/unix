/*
 * =====================================================================================
 *
 *       Filename:  ptrdemo01.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/09/2014 02:14:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	unsigned long a = 1245048;
//	printf("%p\n", *(void**)a);
//	(unsigned int*)0x10000 = 1234;
	char c = 128;
	printf("c=%d\n", c);
	char aa[10];
	printf("%d\n", strlen(aa));
	printf("sizeof(int) = %d\n", sizeof(int));
	printf("sizeof(long) = %d\n", sizeof(long));
	printf("sizeof(*) = %d\n", sizeof(void*));
	return 0;
}
