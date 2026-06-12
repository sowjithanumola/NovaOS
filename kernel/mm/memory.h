/*
 * NovaOS Memory Management Header
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "../include/types.h"

/* Page flags */
#define PAGE_PRESENT  0x01
#define PAGE_WRITE    0x02
#define PAGE_USER     0x04

void init_memory(void);
void setup_paging(void);
void map_pages(uint64_t virt, uint64_t phys, uint64_t size, uint32_t flags);
void map_page(uint64_t virt, uint64_t phys, uint32_t flags);
void init_heap(void);
void *malloc(size_t size);
void free(void *ptr);

/* Heap management */
void heap_init(uint64_t base, uint64_t size);
void *heap_alloc(size_t size);
void heap_free(void *ptr);

#endif
