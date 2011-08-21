

#ifndef LIBXMEM_H_
#define LIBXMEM_H_

#define FIRSTFIT 1
#define BESTFIT 2
#define WORSTFIT 3
#define QUICKFIT 4

#ifndef STRATEGY
#define STRATEGY FIRSTFIT /* default search strategy */
#endif

/* minimum units to morecore() will request from sbrk() */
#define NALLOC 1024

typedef long Align;	/* for alignment to long boundary */

union header {	/* block header */
	struct {
		union header *next; /* next block if on free list */
		unsigned size;	/* size of this block */
	} s;

	Align x;	/* force alignment of blocks */
};

typedef union header Header;

void *malloc(size_t size);
void free(void *ptr);
//void *realloc(void *ptr, size_t size);
static Header *morecore(unsigned units);

#endif /* LIBXMEM_H_ */
