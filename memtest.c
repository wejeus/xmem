
#include <stdio.h>
#include "libxmem.h"

int main(int argc, char **argv) {

	printf("-- START XMEMTEST");
	
	int *p1 = xmalloc(100*sizeof(int));
	p1[1] = 4711;
	printf("\n*p1: %d", p1[1]);
	xfree(p1);
		
	// int *p2 = xmalloc(sizeof(int));
	// int *a1 = xmalloc(1000*sizeof(int));
	// a1[0] = 0;
	// a1[1] = 1;
	// a1[9] = 9;
	// printf("\na1[]: %d %d %d", a1[0], a1[1], a1[9]);
	// xfree(a1);
	// int *p3 = xmalloc(sizeof(int));
	// *p2 = 13;
	// *p3 = 666;
	// xfree(p2);
	// xfree(p3);
	
	int *p4 = xmalloc(sizeof(int));
	*p4 = 666;
	printf("\n*p4: %d", *p4);
	xfree(p4);
	
	printf("\n-- XMEMTEST DONE!\n");
	return 0;
}
