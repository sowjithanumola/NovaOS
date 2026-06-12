/*
 * NovaOS Shell Header
 */

#ifndef __SHELL_H__
#define __SHELL_H__

#include "../kernel/include/types.h"

void shell_main(void);
void shell_read_command(void);
void shell_execute_command(const char *cmd_line);
uint8_t getchar(void);

#endif
