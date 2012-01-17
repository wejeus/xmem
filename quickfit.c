
#include "quickfit.h"
#include <stdio.h>

void quickfit_free(void *ptr) {
	printf("quickfit free\n");
}


void *quickfit_malloc(size_t size) {
	printf("quickfit malloc\n");
}


void *quickfit_realloc(void *ptr, size_t size) {
	printf("quickfit realloc\n");
}