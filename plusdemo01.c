/*
 * =====================================================================================
 *
 *       Filename:  plusdemo01.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2014 04:15:27 PM
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

int main() {
	int a = 5, b = 7, c, d = 4;
	c = a +++ b;
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	d += (d++);
	printf("%d\n", d);
	int e = 4;
	e += (++e);
	printf("%d\n", e);
	return 0;
}
