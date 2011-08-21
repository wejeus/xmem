
#include <unistd.h>
#include "libxmem.h"
#include "debug.c"


/* empty list to get started */
static Header base_block;
/* start of free list */
static Header *p_free_blocks = NULL;


/* xmalloc: general-purpose storage allocator */
void *malloc(size_t size) {
	return m_malloc(size, FIRSTFIT);
}


void free(void *ptr) {
	return m_free(ptr, FIRSTFIT);
}


/* morecore: ask system for more memory
 * Gets more memory from system by increasing the heap with a sbrk() call.
 * The pointer returned from sbrk() is will be the pointer to the Header
 * of this new block. The block is inserted into the private list of free
 * memory by calling the private function free() */
static Header *morecore(unsigned units) {
	char *cp;
	Header *new_block;
	
	if (units < NALLOC)
		units = NALLOC;
	
	/* if sbrk() is successful a new pointer to the BASE
	 * of the newly allocated memory is returned */
	cp = sbrk(units * sizeof(Header));
	
	 /* sbrk() was unable to allocate more space */
	if (cp == (char *) -1)
		return NULL;
	
	/* insert new memory block into list of free blocks */
	new_block = (Header *) cp;
	new_block->s.size = units;
	free((void *)(new_block+1));

	return p_free_blocks;
}

