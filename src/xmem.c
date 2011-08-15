
#include "xmem.h"


/* empty list to get started */
static Header base_block;
/* start of free list */
static Header *p_free_blocks = NULL;


/* xmalloc: general-purpose storage allocator */
void *xmalloc(unsigned num_bytes) {
	if(DEBUG_MALLOC) printf("Start xmalloc.\n");

	/* temp blocks used to handle next/prev location */
	Header *p, *prev_block;
	unsigned num_units;

	/* calculate the number of blocks needed */
	num_units = (num_bytes+sizeof(Header)-1)/sizeof(Header) + 1;

	/* runs on every call to assign prev_block an adress.
	 * If no free list yet, exp evaluates to NULL and
	 * base, prev and free is linked into a chain of size 0,
	 * which will trigger a call for more memory later. */
	if ((prev_block = p_free_blocks) == NULL) {
		base_block.s.next = p_free_blocks = prev_block = &base_block;
		base_block.s.size = 0;
	}

	/* on start p is set to point to the first free block.
	 * In the following iterations p points to the next free block to
	 * be examined and prev_block to the previous free block. */
	for (p = prev_block->s.next; ; prev_block = p, p = p->s.next) {
		/* test if current block is big enough */
		if (p->s.size >= num_units) {
			/* test if current block fits requested amount exactly
			 * if so, unlink from list. */
			if (p->s.size == num_units)
				prev_block->s.next = p->s.next;
			/* allocate tail end */
			else {
				p->s.size -= num_units;
				p += p->s.size;
				p->s.size = num_units;
			}

			/* reset list of free space point to the last examined
			 * block of free space. This also means that all following
			 * calls to xmalloc will start its search on some
			 * arbitrary position in the list. */
			p_free_blocks = prev_block;

			/* increase the block pointer by one so the callee dont
			 * receive the adress of this blocks header but instead
			 * the newly allocated memory requested. */
			return (void *)(p+1);

		}


		/* wrapped around free list, meaning: if true we searched the entire
		 * list without finding enough free memory to allocate. Since C uses
		 * 'sloppy' logic, the second expression will not be evaluated unless
		 * p != p_free_blocks. If memcore fails to allocate mem, return null. */
		if (p == p_free_blocks && (p = morecore(num_units)) == NULL)
				return NULL;
	}

}


#define NALLOC 1024	/* minimum #units to request */

/* morecore: ask system for more memory
 * Gets more memory from system by increasing the heap with a sbrk() call.
 * The pointer returned from sbrk() is will be the pointer to the Header
 * of this new block. The block is inserted into the private list of free
 * memory by calling the private function free() */
static Header *morecore(unsigned requested_num_units) {
	char *cp;
	Header *new_block;
	
	if (requested_num_units < NALLOC)
		requested_num_units = NALLOC;
	
	/* if sbrk() is successful a new pointer to the BASE
	 * of the newly allocated memory is returned */
	cp = sbrk(requested_num_units * sizeof(Header));
	
	 /* sbrk() was unable to allocate more space */
	if (cp == (char *) -1)
		return NULL;
	
	/* insert new memory block into list of free blocks */
	new_block = (Header *) cp;
	new_block->s.size = requested_num_units;
	xfree((void *)(new_block+1));

	return p_free_blocks;
}

/* free: put back block ap in free list */
void xfree(void *allocated_memory) {
	
	Header *bp, *p;
	/* point to block header */
	bp = (Header *)allocated_memory - 1;
	
	for (p = p_free_blocks; !(bp > p && bp < p->s.next); p = p->s.next)
		if (p >= p->s.next && (bp > p || bp < p->s.next))
			break; /* freed block at start or end of arena */

	if (bp + bp->s.size == p->s.next) {
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	} else 
		bp->s.next = p->s.next;
	
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	} else 
		p->s.next = bp;
	
	p_free_blocks = p;
}



