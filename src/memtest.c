
#include <stdio.h>
#include "libxmem/libxmem.h"

int main (int argc, char **argv) {

	printf("XMEMTEST\n\n");

	int *p;
	printf("Before xmalloc, p points to: %p\n", p);
	p = (int*) xmalloc(sizeof(int));
	printf("After xmalloc, p points to: %p\n", p);
	return 0;
}
