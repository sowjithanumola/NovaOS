/*
 * NovaOS Memory Management
 * Virtual memory, paging, and heap allocation
 */

#include "memory.h"
#include "../include/types.h"
#include "../include/stdio.h"

#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12

/**
 * Initialize memory management
 */
void init_memory(void)
{
    kprintf("  [MM] Initializing virtual memory...\n");
    
    /* Initialize page tables */
    setup_paging();
    
    /* Initialize heap allocator */
    init_heap();
    
    kprintf("  [MM] Memory management initialized\n");
}

/**
 * Set up paging structures
 */
void setup_paging(void)
{
    kprintf("  [MM] Setting up paging...\n");
    
    /* Map kernel space */
    map_pages(0xFFFF800000000000, 0x100000, 0x1000000, PAGE_PRESENT | PAGE_WRITE);
    
    kprintf("  [MM] Paging setup complete\n");
}

/**
 * Map a range of pages
 */
void map_pages(uint64_t virtual_addr, uint64_t physical_addr, uint64_t size, uint32_t flags)
{
    uint64_t virt = virtual_addr & ~(PAGE_SIZE - 1);
    uint64_t phys = physical_addr & ~(PAGE_SIZE - 1);
    uint64_t num_pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
    
    for (uint64_t i = 0; i < num_pages; i++) {
        map_page(virt + (i * PAGE_SIZE), phys + (i * PAGE_SIZE), flags);
    }
}

/**
 * Map a single page
 */
void map_page(uint64_t virtual_addr, uint64_t physical_addr, uint32_t flags)
{
    /* Simplified page mapping - full implementation would use page tables */
}

/**
 * Initialize kernel heap
 */
void init_heap(void)
{
    kprintf("  [MM] Initializing kernel heap...\n");
    heap_init(0xFFFF800000100000, 0x400000);
}

/**
 * Allocate memory
 */
void *malloc(size_t size)
{
    return heap_alloc(size);
}

/**
 * Free memory
 */
void free(void *ptr)
{
    heap_free(ptr);
}
