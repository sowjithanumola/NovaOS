# NovaOS Build Configuration

# Cross compiler settings
ARCH := x86_64
CROSS_COMPILE := x86_64-linux-gnu-
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AS := nasm
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy

# Compiler flags
CFLAGS := -m64 -fno-stack-protector -fno-builtin -Wall -Wextra
CFLAGS += -nostdinc -nostdlib -fPIC
CFLAGS += -O2

ASFLAGS := -f elf64

LDFLAGS := -m elf_x86_64 -nostdlib -z max-page-size=0x1000
