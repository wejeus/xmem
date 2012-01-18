
#include "quickfit.h"
#include "linearfit.h"
#include <stdio.h>

/*
Man delar inte upp minnesblocket innan man lämnar ut det via malloc(), 
utan slösar lite med minnet för att få det hela att gå så fort 
som möjligt. Därav namnet “quick fit”. På samma sätt slår man 
heller inte ihop intilliggande block då de återlämnas, utan de länkas 
in direkt i respektive lista. 
*/

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
static Header *free_blocks[NRQUICKLISTS];

static Header *morecore(size_t block_pos);

void quickfit_free(void *ptr) {
	Header *bp = (Header *)ptr - 1;
	
	size_t block_pos = sqrt(bp->s.size) - 4;
	if (block_pos >= NRQUICKLISTS) {
		printf("\nquickfit_free(), within bounds of some quicklist");
		quicklist_free(block_pos, ptr);
	} else {
		printf("\nquickfit_free(), large free requested, doing linear_free(ptr)");
		linear_free(ptr);
	}
}

void quicklist_free(size_t block_pos, void *ptr) {
	
}

void *quickfit_malloc(size_t size) {
	printf("\nquickfit_malloc");

	/* calculate the number of blocks needed */
	unsigned num_units = (size+sizeof(Header)-1)/sizeof(Header) + 1;

	size_t block_pos = sqrt(num_units) - 4;
	if (block_pos >= NRQUICKLISTS) {
		printf("\nwithin bounds of some quicklist");
		return quicklist_malloc(block_pos, num_units);
	} else {
		printf("\nlarge mem requested, doing linear_malloc(size)");
		return linear_malloc(size);
	}
}

void *quicklist_malloc(size_t block_pos, unsigned num_units) {
	
	// /* temp blocks used to handle next/prev location */
	// Header *cur_block, *prev_block;
	// 
	// /* runs on every call to assign prev_block an adress.
	//  * If no free list yet, exp evaluates to NULL and
	//  * base, prev and free is linked into a chain of size 0,
	//  * which will trigger a call for more memory later. */
	// if ((prev_block = free_blocks) == NULL) {
	// 	base_block.s.next = free_blocks = prev_block = &base_block;
	// 	base_block.s.size = 0;
	// }
	// 
	// /* on start p is set to point to the first free block.
	//  * In the following iterations p points to the next free block to
	//  * be examined and prev_block to the previous free block. */
	// for (cur_block = prev_block->s.next; ; prev_block = cur_block, cur_block = cur_block->s.next) {
	// 
	// 	/* test if current block is big enough */
	// 	if (cur_block->s.size >= num_units) {
	// 		/* test if current block fits requested amount exactly
	// 		 * if so, unlink from list. */
	// 		if (cur_block->s.size == num_units)
	// 			prev_block->s.next = cur_block->s.next;
	// 		/* allocate tail end */
	// 		else {
	// 			cur_block->s.size -= num_units;
	// 			cur_block += cur_block->s.size;
	// 			cur_block->s.size = num_units;
	// 		}
	// 
	// 		/* reset list of free space point to the last examined
	// 		 * block of free space. This also means that all following
	// 		 * calls to xmalloc will start its search on some
	// 		 * arbitrary position in the list. */
	// 		free_blocks = prev_block;
	// 
	// 		/* increase the block pointer by one so the callee dont
	// 		 * receive the adress of this blocks header but instead
	// 		 * the newly allocated memory requested. */
	// 		return (void *)(cur_block+1);
	// 	}
	// 	/* wrapped around free list, meaning: if true we searched the entire
	// 	 * list without finding enough free memory to allocate. Since C uses
	// 	 * 'sloppy' logic, the second expression will not be evaluated unless
	// 	 * p != p_free_blocks. If memcore fails to allocate mem, return null. */
	// 	if (cur_block == free_blocks && (cur_block = morecore(block_pos,num_units)) == NULL)
	// 			return NULL;
	// }
}


void *quickfit_realloc(void *ptr, size_t size) {
	printf("\nquickfit realloc");
}


static Header *morecore(size_t block_pos) {
	printf("\nquickfit_morecore");
	
	char *cp;
	Header *new_block;
	unsigned units = pow(2, block_pos);
	
	/* if sbrk() is successful a new pointer to the BASE
	 * of the newly allocated memory is returned, allocates size of
	 * quicklist position */
	cp = sbrk(units * sizeof(Header));
	
	 /* sbrk() was unable to allocate more space */
	if (cp == (char *) -1)
		return NULL;
	
	/* insert new memory block into list of free blocks */
	new_block = (Header *) cp;
	new_block->s.size = units;

	/* add new memory area to list of free memory */
	quicklist_free(block_pos, (void *)(new_block+1));

	return free_blocks;
}