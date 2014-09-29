/*
 * =====================================================================================
 *
 *       Filename:  getmemorydemo01.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2014 04:43:58 PM
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

char* getMemory(void) {
	static char p[] = "hello world!\n";
	return p;
}

int main() {
	char *str = NULL;
	str = getMemory();
	printf(str);

	return 0;
}
