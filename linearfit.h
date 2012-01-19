/* 
 * Author: Samuel Wejeus
 * Contact: particlewave at opera dot com
 * Use as you see fit and if you do please send me a mail =)
 */


#ifndef LINEARFIT_H_
#define LINEARFIT_H_

#include <unistd.h>

void linear_free(void *ptr);
void *linear_malloc(size_t size);
void *linear_realloc(void *ptr, size_t size);

#endif /* LINEARFIT_H_ */