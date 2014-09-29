/*
 * =====================================================================================
 *
 *       Filename:  strcpy.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/09/2014 01:32:08 PM
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
	char a;
	char *str = &a;
	strcpy(str, "hello\n");
	printf("%s", str);
	return 0;
}
