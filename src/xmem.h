/*
 * xmem.h
 *
 *  Created on: Jul 24, 2011
 *      Author: shazam
 */

#ifndef XMEM_H_
#define XMEM_H_

#include <unistd.h>
#include <stdio.h>

#define DEBUG_MALLOC 1
#define DEBUG_MORECORE 1

#define FIRSTFIT 1
#define BESTFIT 2
#define WORSTFIT 3
#define QUICKFIT 4

#if !defined(STRATEGY)
#define STRATEGY FIRSTFIT /* default search strategy */
#endif

#if !defined(NRQUICKLISTS)
#define NRQUICKLISTS 32
#endif

typedef long Align;	/* for alignment to long boundary */

union header {	/* block header */
	struct {
		union header *next; /* next block if on free list */
		unsigned size;	/* size of this block */
	} s;

	Align x;	/* force alignment of blocks */
};

typedef union header Header;

void *xmalloc(unsigned num_bytes);
static Header *morecore(unsigned requested_num_units);
void xfree(void *allocated_memory);


#endif /* XMEM_H_ */
