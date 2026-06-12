/*
 * NovaOS Shell Implementation
 */

#include "shell.h"
#include "../kernel/include/types.h"
#include "../kernel/include/stdio.h"
#include "../kernel/include/string.h"

#define COMMAND_BUFFER_SIZE 256

static char input_buffer[COMMAND_BUFFER_SIZE];
static uint32_t input_length = 0;

/* Built-in commands */
typedef struct {
    const char *name;
    void (*handler)(int argc, char **argv);
    const char *help;
} builtin_command_t;

static void cmd_help(int argc, char **argv);
static void cmd_clear(int argc, char **argv);
static void cmd_echo(int argc, char **argv);
static void cmd_uname(int argc, char **argv);
static void cmd_exit(int argc, char **argv);

static builtin_command_t builtin_commands[] = {
    {"help", cmd_help, "Display help information"},
    {"clear", cmd_clear, "Clear the screen"},
    {"echo", cmd_echo, "Echo text"},
    {"uname", cmd_uname, "Print system information"},
    {"exit", cmd_exit, "Exit the shell"},
    {NULL, NULL, NULL}
};

/**
 * Shell main loop
 */
void shell_main(void)
{
    kprintf("\n");
    kprintf("========================================\n");
    kprintf("      NovaOS Command Shell v1.0\n");
    kprintf("========================================\n");
    kprintf("Type 'help' for a list of commands\n\n");
    
    while (1) {
        kprintf("NovaOS> ");
        shell_read_command();
        
        if (input_length > 0) {
            shell_execute_command(input_buffer);
            input_length = 0;
        }
    }
}

/**
 * Read command from keyboard
 */
void shell_read_command(void)
{
    input_length = 0;
    memset(input_buffer, 0, COMMAND_BUFFER_SIZE);
    
    while (1) {
        uint8_t c = getchar();
        
        if (c == '\n' || c == '\r') {
            putchar('\n');
            input_buffer[input_length] = '\0';
            break;
        } else if (c == 8 || c == 127) {  /* Backspace */
            if (input_length > 0) {
                input_length--;
                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
        } else if (input_length < COMMAND_BUFFER_SIZE - 1) {
            input_buffer[input_length++] = c;
            putchar(c);
        }
    }
}

/**
 * Execute shell command
 */
void shell_execute_command(const char *cmd_line)
{
    char cmd_copy[COMMAND_BUFFER_SIZE];
    strcpy(cmd_copy, cmd_line);
    
    /* Simple parsing - split by spaces */
    char *argv[16];
    int argc = 0;
    
    char *token = strtok_r(cmd_copy, " ", NULL);
    while (token && argc < 15) {
        argv[argc++] = token;
        token = strtok_r(NULL, " ", NULL);
    }
    
    if (argc == 0) return;
    
    /* Look for built-in command */
    for (int i = 0; builtin_commands[i].name; i++) {
        if (strcmp(argv[0], builtin_commands[i].name) == 0) {
            builtin_commands[i].handler(argc, argv);
            return;
        }
    }
    
    kprintf("Command not found: %s\n", argv[0]);
}

/* Built-in command implementations */

static void cmd_help(int argc, char **argv)
{
    kprintf("Available commands:\n");
    for (int i = 0; builtin_commands[i].name; i++) {
        kprintf("  %-10s - %s\n", builtin_commands[i].name, builtin_commands[i].help);
    }
}

static void cmd_clear(int argc, char **argv)
{
    uint16_t *vga = (uint16_t *)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga[i] = 0x0F20;
    }
    vga_row = 0;
    vga_col = 0;
}

static void cmd_echo(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        kprintf("%s", argv[i]);
        if (i < argc - 1) kprintf(" ");
    }
    kprintf("\n");
}

static void cmd_uname(int argc, char **argv)
{
    kprintf("NovaOS v1.0 64-bit\n");
}

static void cmd_exit(int argc, char **argv)
{
    kprintf("Goodbye!\n");
    while (1) {
        asm volatile("cli; hlt");
    }
}

/* Helper functions */

uint8_t getchar(void)
{
    return 'a';  /* Placeholder */
}

char *strtok_r(char *str, const char *delim, char **saveptr)
{
    if (str) {
        *saveptr = str;
    }
    
    if (!*saveptr || !**saveptr) return NULL;
    
    str = *saveptr;
    while (*str && strchr(delim, *str)) str++;
    
    if (!*str) return NULL;
    
    char *start = str;
    while (*str && !strchr(delim, *str)) str++;
    
    if (*str) {
        *str++ = '\0';
    }
    
    *saveptr = str;
    return start;
}

static int strchr(const char *str, char c)
{
    while (*str) {
        if (*str == c) return 1;
        str++;
    }
    return 0;
}
