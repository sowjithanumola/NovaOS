/*
 * NovaOS Heap Allocator
 * Simple malloc/free implementation
 */

#include "heap.h"
#include "../include/types.h"
#include "../include/string.h"

#define HEAP_MAGIC 0xDEADBEEF

typedef struct heap_block {
    uint32_t magic;
    size_t size;
    int free;
    struct heap_block *next;
    struct heap_block *prev;
} heap_block_t;

static heap_block_t *heap_start = NULL;
static uint64_t heap_base = 0;
static uint64_t heap_size = 0;

/**
 * Initialize heap allocator
 */
void heap_init(uint64_t base, uint64_t size)
{
    heap_base = base;
    heap_size = size;
    
    /* Create initial heap block */
    heap_start = (heap_block_t *)base;
    heap_start->magic = HEAP_MAGIC;
    heap_start->size = size - sizeof(heap_block_t);
    heap_start->free = 1;
    heap_start->next = NULL;
    heap_start->prev = NULL;
}

/**
 * Allocate memory from heap
 */
void *heap_alloc(size_t size)
{
    heap_block_t *current = heap_start;
    
    /* Find suitable block */
    while (current != NULL) {
        if (current->free && current->size >= size) {
            /* Split block if needed */
            if (current->size > size + sizeof(heap_block_t)) {
                heap_block_t *new_block = (heap_block_t *)((uint64_t)current + sizeof(heap_block_t) + size);
                
                new_block->magic = HEAP_MAGIC;
                new_block->size = current->size - size - sizeof(heap_block_t);
                new_block->free = 1;
                new_block->next = current->next;
                new_block->prev = current;
                
                if (current->next) {
                    current->next->prev = new_block;
                }
                
                current->next = new_block;
                current->size = size;
            }
            
            current->free = 0;
            return (void *)((uint64_t)current + sizeof(heap_block_t));
        }
        
        current = current->next;
    }
    
    return NULL;
}

/**
 * Free allocated memory
 */
void heap_free(void *ptr)
{
    if (!ptr) return;
    
    heap_block_t *block = (heap_block_t *)((uint64_t)ptr - sizeof(heap_block_t));
    
    if (block->magic != HEAP_MAGIC) {
        return;  /* Invalid block */
    }
    
    block->free = 1;
    
    /* Coalesce with next block */
    if (block->next && block->next->free) {
        block->size += sizeof(heap_block_t) + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }
    
    /* Coalesce with previous block */
    if (block->prev && block->prev->free) {
        block->prev->size += sizeof(heap_block_t) + block->size;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
    }
}
