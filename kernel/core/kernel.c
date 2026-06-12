/*
 * NovaOS Kernel Main
 * Core kernel initialization
 */

#include "kernel.h"
#include "../include/types.h"
#include "../include/stdio.h"

/* Forward declarations */
void init_gdt(void);
void init_idt(void);
void init_memory(void);
void init_scheduler(void);

/**
 * Kernel main entry point
 * Called from kernel_entry.asm after bootloader setup
 */
void kmain(void)
{
    /* Initialize VGA text mode for output */
    init_vga_text_mode();
    
    kprintf("============================================="\n");
    kprintf("        NovaOS Kernel v1.0\n");
    kprintf("============================================="\n\n");
    
    kprintf("[KERNEL] Initializing GDT...\n");
    init_gdt();
    
    kprintf("[KERNEL] Initializing IDT...\n");
    init_idt();
    
    kprintf("[KERNEL] Initializing memory management...\n");
    init_memory();
    
    kprintf("[KERNEL] Initializing process scheduler...\n");
    init_scheduler();
    
    kprintf("\n[KERNEL] All systems initialized successfully!\n");
    kprintf("[KERNEL] Dropping to shell...\n\n");
    
    /* Start the shell or first process */
    shell_main();
    
    /* Should not reach here */
    kernel_panic("Kernel returned from shell");
}

/**
 * Initialize VGA text mode for early debug output
 */
void init_vga_text_mode(void)
{
    /* Clear VGA text mode buffer */
    uint16_t *vga_buffer = (uint16_t *)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = 0x0F20;  /* White text on black background, space char */
    }
    
    /* Initialize cursor */
    vga_row = 0;
    vga_col = 0;
}

/**
 * Kernel panic - unrecoverable error
 */
void kernel_panic(const char *message)
{
    cli();
    kprintf("\n!!! KERNEL PANIC !!!\n");
    kprintf("Error: %s\n", message);
    kprintf("System halted.\n");
    
    while (1) {
        hlt();
    }
}

/**
 * CPU halt instruction
 */
void hlt(void)
{
    asm volatile("hlt");
}

/**
 * Clear interrupts
 */
void cli(void)
{
    asm volatile("cli");
}

/**
 * Enable interrupts
 */
void sti(void)
{
    asm volatile("sti");
}
