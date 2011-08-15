/*
 * xmemtest.c
 *
 *  Created on: Jul 24, 2011
 *      Author: shazam
 */

#include <stdio.h>
#include "xmem.h"

int main (int argc, char **argv) {
	printf("XMEMTEST\n\n");

	int *p;
	printf("Before xmalloc, p points to: %p\n", p);
	p = (int*) xmalloc(1*sizeof(int));
	printf("After xmalloc, p points to: %p\n", p);
	return 0;
}
