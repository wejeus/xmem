
#include <unistd.h>

#include "libxmem.h"
#include "libxmem_interface.h"

extern struct LIBXMEM_INTERFACE XMEM_CALLBACK;

void *xmalloc(size_t size) {
	// printf("In xmalloc (libxmem)\n");
	return XMEM_CALLBACK.XMEM_malloc(size);
}


void xfree(void *ptr) {
	// printf("In xfree (libxmem)\n");
	return XMEM_CALLBACK.XMEM_free(ptr);
}


void *xrealloc(void *ptr, size_t size) {
	//TODO
}

