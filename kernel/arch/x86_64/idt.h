/*
 * NovaOS IDT Header
 */

#ifndef __IDT_H__
#define __IDT_H__

void init_idt(void);
void generic_interrupt_handler(uint32_t int_num);

#endif
