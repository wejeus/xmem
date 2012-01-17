
#ifndef QUICKFIT_H_
#define QUICKFIT_H_

#include <unistd.h>

#ifndef NRQUICKLISTS
#define NRQUICKLISTS 32
#endif

void quickfit_free(void *ptr);
void *quickfit_malloc(size_t size);
void *quickfit_realloc(void *ptr, size_t size);

#endif /* QUICKFIT_H_ */