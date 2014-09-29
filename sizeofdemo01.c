/*
 * =====================================================================================
 *
 *       Filename:  sizeofdemo01.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2014 04:28:17 PM
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

void fun(char s[100]) {
	printf("sizeof(s):%d\n", sizeof(s));
}

int main() {
	char str[] = "http://www.ibegroup.com/";
	char s[100];
	char *p = str;
	int n = 10;
	void *q = malloc(100);

	printf("sizeof(str):%d\n", sizeof(str));
	printf("sizeof(p):%d\n", sizeof(p));
	printf("sizeof(n):%d\n", sizeof(n));
	printf("sizeof(q):%d\n", sizeof(q));
	
	fun(s[100]);

	return 0;
}
