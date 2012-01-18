
#include "linearfit.h"
#include "params.h"
#include <stdio.h>

/* for alignment to long boundary */
typedef long Align;

/* block header */
union header {
	struct {
		/* next block if on free list */
		union header *next;
		/* size of this block */
		unsigned size;
	} s;
	/* force alignment of blocks */
	Align x;
};

typedef union header Header;

/* empty list to get started */
static Header base_block;
/* start of free list */
static Header *p_free_blocks = NULL;


/* minimum units to morecore() will request from sbrk() */
#define NALLOC 1024
static Header *morecore(unsigned units);
void *firstfit(Header *prev_block, unsigned num_units);
void *bestfit(Header *prev_block, unsigned num_units);
void *worstfit(Header *prev_block, unsigned num_units);


// TODO: bestfit, worstfit
void *linear_malloc(size_t size) {
	printf("\nlinear_malloc, using strategy: %d", STRATEGY);
	
	/* temp blocks used to handle next/prev location */
	Header *p, *prev_block;
	unsigned num_units;

	/* calculate the number of blocks needed */
	num_units = (size+sizeof(Header)-1)/sizeof(Header) + 1;

	/* runs on every call to assign prev_block an adress.
	 * If no free list yet, exp evaluates to NULL and
	 * base, prev and free is linked into a chain of size 0,
	 * which will trigger a call for more memory later. */
	if ((prev_block = p_free_blocks) == NULL) {
		base_block.s.next = p_free_blocks = prev_block = &base_block;
		base_block.s.size = 0;
	}

	switch (STRATEGY) {
		case FIRSTFIT:
			return firstfit(prev_block, num_units);
		case BESTFIT:
			return bestfit(prev_block, num_units);
		case WORSTFIT:
			return worstfit(prev_block, num_units);
		default:
			return NULL;
	}
}

void *firstfit(Header *prev_block, unsigned num_units) {
	printf("\n(void*) firstfit(...)");
	
	Header *p;
	
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

void *bestfit(Header *prev_block, unsigned num_units) {
	printf("\n(void*) bestfit(...), looking for blocksize: %d", num_units);
	Header *p;
	Header *currentBest = NULL;
	Header *currentBestPrev = NULL;
	
	for (p = prev_block->s.next; ; prev_block = p, p = p->s.next) {
		if (p->s.size >= num_units) {
			
			if (currentBest == NULL) {
				printf("\nfound first suitable block, size: %d", p->s.size);
				currentBest = p;
				currentBestPrev = prev_block;
			} else {
				if (p->s.size < currentBest->s.size) {
					printf("\nfound better block, size: %d", p->s.size);	
					currentBest = p;
					currentBestPrev = prev_block;
				}
			}
		}
		
		if ( (p == p_free_blocks) && (currentBest != NULL) ) {
			/* unhook form list, split block if needed */
			if (currentBest->s.size == num_units)
				currentBestPrev->s.next = currentBest->s.next;
			else {
				currentBest->s.size -= num_units;
				currentBest += p->s.size;
				currentBest->s.size = num_units;
			}
			p_free_blocks = prev_block;
			return (void *)(currentBest+1);
		}
		
		/* Reached end of list, if suitable block is found return it
		 * otherwise request morecore. */
		if ( (p == p_free_blocks) && ((p = morecore(num_units)) == NULL) ) {
			return NULL;
		}
		
	}	
}

void *worstfit(Header *prev_block, unsigned num_units) {
	printf("\n(void*) worstfit(...)");
	Header *p;
	
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

/* free: put back block ap in free list */
void linear_free(void *ptr) {
	printf("\nlinear_free");
	
	Header *bp, *p;
	/* point to block header */
	bp = (Header *)ptr - 1;
	
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


void *linear_realloc(void *ptr, size_t size) {
	
}


/* morecore: ask system for more memory
 * Gets more memory from system by increasing the heap with a sbrk() call.
 * The pointer returned from sbrk() is will be the pointer to the Header
 * of this new block. The block is inserted into the private list of free
 * memory by calling the private function free() */
static Header *morecore(unsigned units) {
	printf("\nlinear_morecore");
	
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

	// TODO, not sure why its here... ------------------------------------------
	linear_free((void *)(new_block+1));

	return p_free_blocks;
}
