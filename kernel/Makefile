# NovaOS Kernel Makefile

include ../config/config.mk

# Kernel source files
KERNEL_SRCS := core/kernel.c \
               mm/memory.c \
               mm/heap.c \
               proc/scheduler.c \
               arch/x86_64/gdt.c \
               arch/x86_64/idt.c \
               lib/stdio.c \
               lib/string.c

KERNEL_ASMS := core/main.asm

KERNEL_OBJS := $(KERNEL_ASMS:.asm=.o) $(KERNEL_SRCS:.c=.o)

KERNEL_TARGET := ../build/kernel.elf

# Default target
all: $(KERNEL_TARGET)

$(KERNEL_TARGET): $(KERNEL_OBJS)
	@mkdir -p ../build
	$(LD) $(LDFLAGS) -T../linker/kernel.ld -o $@ $^
	@echo "[✓] Kernel built: $@"

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -delete
	rm -f $(KERNEL_TARGET)

.PHONY: all clean
