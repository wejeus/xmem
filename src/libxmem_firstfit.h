
/* fucked up, i should be able to use 
* free(..), malloc(..) not m_*.. (different sigs) */
void m_free(void *ptr, int strategy);
void *m_malloc(size_t size, int strategy);