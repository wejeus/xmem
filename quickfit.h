
#ifndef QUICKFIT_H_
#define QUICKFIT_H_

#include <unistd.h>

/* block sizes for quicklist should be increasing on a factor 
 * of 2 starting with 8, so: 8, 16, 32.. */
#ifndef NRQUICKLISTS
#define NRQUICKLISTS 3
#endif

void quickfit_free(void *ptr);
void *quickfit_malloc(size_t size);
void *quickfit_realloc(void *ptr, size_t size);

#endif /* QUICKFIT_H_ */