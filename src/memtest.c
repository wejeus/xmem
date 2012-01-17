
#include <stdio.h>
#include "libxmem.h"

int main(int argc, char **argv) {

	printf("-- START XMEMTEST");
	
	int *p;
	p = xmalloc(sizeof(p));
	*p = 1;
	xfree(p);
	
	printf("\n-- XMEMTEST DONE!\n");
	return 0;
}
