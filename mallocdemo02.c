/*
 *
 * =====================================================================================
 *
 *       Filename:  mallocdemo02.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2014 04:05:40 PM
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
#include <malloc.h>

int main() {
	char* ptr;
	ptr = (char*)malloc(0);
	printf("%u\n",(int)malloc_usable_size(ptr));
	ptr = (char*)malloc(15);
	printf("%u\n", (int)malloc_usable_size(ptr));
	ptr = (char*)malloc(25);
	printf("%u\n", (int)malloc_usable_size(ptr));
	ptr = (char*)malloc(40);
	printf("%u\n", (int)malloc_usable_size(ptr));
	ptr = (char*)malloc(48);
	printf("%u\n", (int)malloc_usable_size(ptr));
	ptr = (char*)malloc(49);
	printf("%u\n", (int)malloc_usable_size(ptr));
	ptr = (char*)malloc(60);
	printf("%u\n", (int)malloc_usable_size(ptr));
	free(ptr);
	return 0;
}
