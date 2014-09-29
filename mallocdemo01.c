/*
 * =====================================================================================
 *
 *       Filename:  mallocdemo01.c
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  09/06/2014 03:51:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

int main() {
	char* ptr = malloc(0);
	if (ptr == NULL)
		puts("null pointer");
	else
		puts("valid pointer");
	return 0;
}
