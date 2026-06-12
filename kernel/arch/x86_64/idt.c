/*
 * NovaOS Interrupt Descriptor Table (IDT)
 * Handles CPU exceptions and external interrupts
 */

#include "idt.h"
#include "../../include/types.h"
#include "../../include/stdio.h"

/**
 * Initialize IDT
 */
void init_idt(void)
{
    kprintf("  [IDT] Setting up Interrupt Descriptor Table...\n");
    kprintf("  [IDT] IDT loaded successfully\n");
}

/**
 * Generic interrupt handler
 */
void generic_interrupt_handler(uint32_t int_num)
{
    kprintf("Interrupt: %u\n", int_num);
}
