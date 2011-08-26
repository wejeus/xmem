
#include <unistd.h>

#include "libxmem.h"
#include "linearfit.h"

void *xmalloc(size_t size) {
	void *ptr = m_malloc(size, FIRSTFIT);
	return ptr;
}


void free(void *ptr) {
	return m_free(ptr, FIRSTFIT);
}


void *realloc(void *ptr, size_t size) {
	//TODO
}

