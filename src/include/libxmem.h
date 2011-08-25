

#ifndef LIBXMEM_H_
#define LIBXMEM_H_

#define FIRSTFIT 1
#define BESTFIT 2
#define WORSTFIT 3
#define QUICKFIT 4

#ifndef STRATEGY
#define STRATEGY FIRSTFIT /* default search strategy */
#endif


void *xmalloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);


#endif /* LIBXMEM_H_ */
