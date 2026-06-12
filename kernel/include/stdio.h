/*
 * NovaOS Standard I/O
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#include "types.h"

/* VGA text mode output */
extern uint32_t vga_row;
extern uint32_t vga_col;

void putchar(char c);
void puts(const char *str);
void kprintf(const char *format, ...);

#endif
