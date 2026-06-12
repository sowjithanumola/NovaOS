/*
 * NovaOS Heap Allocator Header
 */

#ifndef __HEAP_H__
#define __HEAP_H__

#include "../include/types.h"

void heap_init(uint64_t base, uint64_t size);
void *heap_alloc(size_t size);
void heap_free(void *ptr);

#endif
