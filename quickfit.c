/* 
 * Author: Samuel Wejeus
 * Contact: particlewave at opera dot com
 * Use as you see fit and if you do please send me a mail =)
 */

#include "quickfit.h"
#include "linearfit.h"
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
// static Header base_block;

/* start of free list */
static Header *free_blocks[NRQUICKLISTS];

static Header *morecore(int block_pos);
void quicklist_free(int block_pos, void *ptr);
void *quicklist_malloc(int block_pos, unsigned num_units);

void quickfit_free(void *ptr) {
	Header *bp = (Header *)ptr - 1;
	
	size_t block_pos = sqrt(bp->s.size) - 4;
	if (block_pos <= NRQUICKLISTS) {
		printf("\nquickfit_free(), within bounds of some quicklist");
		quicklist_free(block_pos, ptr);
	} else {
		printf("\nquickfit_free(), large free requested, doing linear_free(ptr)");
		linear_free(ptr);
	}
}

void quicklist_free(int block_pos, void *ptr)
{
	printf("\nquicklist_free");
	Header *tmp = free_blocks[block_pos];
	
	if (tmp == NULL) {
		/* nothing to connect to! */
		printf("\nnothing to connect to!");
		free_blocks[block_pos] = (Header *) ptr-1;
	} else {
		/* relink with old blocks */
		printf("\nrelink with old blocks");
		free_blocks[block_pos] = (Header *) ptr-1;
		Header *next = free_blocks[block_pos]->s.next;
		while ( (next = next->s.next) != NULL) {
			printf("\ntraversing..");
		}
		next = tmp;	
	}	
}

void *quickfit_malloc(size_t size) {
	printf("\nquickfit_malloc, requested size: %d", size);

	/* calculate the number of blocks needed */
	unsigned num_units = (size+sizeof(Header)-1)/sizeof(Header) + 1;

	int block_pos = sqrt(size) - 4;
	if (block_pos <= 0) block_pos = 0;
	
	printf("\nsquareroot of req units (minus 4, smalles quicklist block is 8): %d", block_pos);
	printf("\n%d <= %d ?", block_pos, NRQUICKLISTS);
	
	if (block_pos <= NRQUICKLISTS) {
		printf("\nwithin bounds of some quicklist");
		return quicklist_malloc(block_pos, size);
	} else {
		printf("\nlarge mem requested, doing linear_malloc(size)");
		return linear_malloc(size);
	}
}

void *quicklist_malloc(int block_pos, unsigned num_units) {	

	Header *next_block = free_blocks[block_pos];
	
	if (next_block == NULL) {
		printf("\nempty list for block size: %d", block_pos);
		/* no more free memory on list, request more core */
		free_blocks[block_pos] = morecore(block_pos);
		if (free_blocks[block_pos] == NULL)
			return NULL;

		next_block = free_blocks[block_pos];
	}
	
	printf("\nreturning first block in list");
	/* return first block on list, we know that the requested size
	 * will fit in this area. Then relink list */
	free_blocks[block_pos] = next_block->s.next;
	return (void *)(next_block+1);
}


void *quickfit_realloc(void *ptr, size_t size) {
	printf("\nquickfit realloc");
}

#define NALLOC_BLOCKS 8

static Header *morecore(int block_pos) {
	printf("\nquickfit_morecore");
	
	char *cp;
	Header *new_block;
	unsigned units = pow(2, block_pos + 4);
	
	printf("\nmorecore will request: %d units", NALLOC_BLOCKS * units);
	
	/* if sbrk() is successful a new pointer to the BASE
	 * of the newly allocated memory is returned, allocates size of
	 * quicklist position */
	cp = sbrk(NALLOC_BLOCKS * units * sizeof(Header));
	
	 /* sbrk() was unable to allocate more space */
	if (cp == (char *) -1)
		return NULL;
	
	/* insert new memory into blocks */
	int i;
	Header *first = (Header *) cp;
	new_block = (Header *) cp;
	new_block->s.size = units;
	for (i = 0; i < NALLOC_BLOCKS-1; ++i) {
		++cp;
		new_block->s.next = (Header *) cp;
		new_block->s.size = units;		
		new_block = new_block->s.next;
	}
	new_block->s.next = NULL;

	/* add new memory area to list of free memory */
	quicklist_free(block_pos, (void *)(first+1));

	return free_blocks[block_pos];
}