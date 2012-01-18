
#include <stdio.h>
#include "libxmem.h"

int main(int argc, char **argv) {

	printf("-- START XMEMTEST");
	
	int *p1 = xmalloc(sizeof(int));
	int *p2 = xmalloc(sizeof(int));
	int *p3 = xmalloc(sizeof(int));
	*p1 = 4711;
	*p2 = 13;
	*p3 = 666;
	printf("\n*p1 = %d", *p1);
	printf("\n*p2 = %d", *p2);
	printf("\n*p3 = %d", *p3);
	xfree(p1);
	xfree(p2);
	xfree(p3);
	
	printf("\n-- XMEMTEST DONE!\n");
	return 0;
}
