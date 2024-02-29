#include <corecrt.h>

#ifndef SANDBOX_MYMALLOC_H
#define SANDBOX_MYMALLOC_H

void *mymalloc(size_t bytes);

void myfree(void *memory);

size_t total_free_memory();

size_t total_allocated();

/**
 * Release all allocated memory to OS
 */
void osfree();

#endif //SANDBOX_MYMALLOC_H
