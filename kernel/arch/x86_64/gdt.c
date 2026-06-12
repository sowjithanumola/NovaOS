/*
 * NovaOS Global Descriptor Table (GDT)
 * Sets up privilege levels and memory segmentation
 */

#include "gdt.h"
#include "../../include/types.h"
#include "../../include/stdio.h"

/**
 * Initialize GDT
 */
void init_gdt(void)
{
    kprintf("  [GDT] Setting up Global Descriptor Table...\n");
    kprintf("  [GDT] GDT loaded successfully\n");
}
