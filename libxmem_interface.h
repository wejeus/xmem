/* 
 * Author: Samuel Wejeus
 * Contact: particlewave at opera dot com
 * Use as you see fit and if you do please send me a mail =)
 */

#ifndef LIBXMEM_INTERFACEH_
#define LIBXMEM_INTERFACE_H_

#include <unistd.h>
#include "params.h"
#include "linearfit.h"
#include "quickfit.h"



/* callback structure */
struct LIBXMEM_INTERFACE {
	void* (*XMEM_malloc)(size_t size);
	void (*XMEM_free)(void *ptr);
	void* (*XMEM_realloc)(void *ptr, size_t size);
};

#if (STRATEGY == FIRSTFIT) || (STRATEGY == BESTFIT) || (STRATEGY == WORSTFIT)
struct LIBXMEM_INTERFACE XMEM_CALLBACK = {
	&linear_malloc,
	&linear_free,
	&linear_realloc
};

#elif STRATEGY == QUICKFIT
struct LIBXMEM_INTERFACE XMEM_CALLBACK = {
	&quickfit_malloc,
	&quickfit_free,
	&quickfit_realloc
};
#endif

#endif /* LIBXMEM_INTERFACEH_ */