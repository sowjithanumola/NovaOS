/*
 * NovaOS Kernel Header
 */

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "../include/types.h"

/* VGA Text Mode Variables */
extern uint32_t vga_row;
extern uint32_t vga_col;

/* Kernel functions */
void kmain(void);
void kernel_panic(const char *message);
void init_vga_text_mode(void);
void hlt(void);
void cli(void);
void sti(void);

/* Shell function */
extern void shell_main(void);

#endif
