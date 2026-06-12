/*
 * NovaOS Standard I/O Implementation
 */

#include "../include/stdio.h"
#include "../include/types.h"
#include "../include/string.h"
#include <stdarg.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BASE 0xB8000

uint32_t vga_row = 0;
uint32_t vga_col = 0;

/**
 * Write character to VGA text mode
 */
void putchar(char c)
{
    uint16_t *vga = (uint16_t *)VGA_BASE;
    
    if (c == '\n') {
        vga_col = 0;
        vga_row++;
        if (vga_row >= VGA_HEIGHT) {
            vga_row = VGA_HEIGHT - 1;
            /* Scroll up */
            for (int i = 0; i < VGA_HEIGHT - 1; i++) {
                for (int j = 0; j < VGA_WIDTH; j++) {
                    vga[i * VGA_WIDTH + j] = vga[(i + 1) * VGA_WIDTH + j];
                }
            }
            for (int j = 0; j < VGA_WIDTH; j++) {
                vga[(VGA_HEIGHT - 1) * VGA_WIDTH + j] = 0x0F00;
            }
        }
    } else if (c == '\r') {
        vga_col = 0;
    } else if (c == '\t') {
        vga_col += 4;
    } else {
        vga[vga_row * VGA_WIDTH + vga_col] = (0x0F << 8) | c;
        vga_col++;
        
        if (vga_col >= VGA_WIDTH) {
            vga_col = 0;
            vga_row++;
            if (vga_row >= VGA_HEIGHT) {
                vga_row = VGA_HEIGHT - 1;
            }
        }
    }
}

/**
 * Write string to VGA
 */
void puts(const char *str)
{
    while (*str) {
        putchar(*str++);
    }
}

/**
 * Simple printf implementation
 */
void kprintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    int val = va_arg(args, int);
                    char buf[32];
                    puts(buf);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    puts(str);
                    break;
                }
                case 'c': {
                    char c = va_arg(args, int);
                    putchar(c);
                    break;
                }
                case '%':
                    putchar('%');
                    break;
            }
        } else {
            putchar(*format);
        }
        format++;
    }
    
    va_end(args);
}
