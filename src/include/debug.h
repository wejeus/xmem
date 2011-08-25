#ifndef _APPLICATION_DEBUG_C_
#define _APPLICATION_DEBUG_C_

#include <stdio.h>

#ifdef DEBUG
#define D(F,V) printf("DEBUG %s:%d:%s() - ", __FILE__, __LINE__, __func__); printf(F,V); printf("\n");
#else
#define D(F,V) /* nothing */
#endif


#endif
