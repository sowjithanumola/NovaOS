# NovaOS BIOS Bootloader Makefile

NASM := nasm
CC := x86_64-linux-gnu-gcc
LD := x86_64-linux-gnu-ld

CFLAGS := -fno-stack-protector -fno-builtin -m64 -c -Wall
LDFLAGS := -m elf_x86_64 -Ttext 0x7C00

# Source files
ASM_SRCS := boot.asm boot32.asm boot64.asm
C_SRCS := 

OBJS := $(ASM_SRCS:.asm=.o) $(C_SRCS:.c=.o)

# Default target
all: bootloader.bin

bootloader.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o bootloader.elf $(OBJS)
	objcopy -O binary bootloader.elf bootloader.bin
	@echo "✓ Built: bootloader.bin"

%.o: %.asm
	$(NASM) -f elf64 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) bootloader.bin bootloader.elf

.PHONY: all clean
