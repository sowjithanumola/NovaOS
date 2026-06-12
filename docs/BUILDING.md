# NovaOS Building Guide

## Prerequisites

- GCC (x86_64 cross-compiler)
- GNU Make
- NASM (Netwide Assembler)
- xorriso (for ISO creation)
- QEMU or VirtualBox (for testing)

## Installation

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    nasm \
    gcc-x86-64-linux-gnu \
    binutils-x86-64-linux-gnu \
    qemu-system-x86 \
    grub-pc-bin \
    xorriso
```

### Fedora
```bash
sudo dnf install -y \
    gcc \
    nasm \
    binutils \
    qemu-system-x86 \
    grub2-tools \
    xorriso
```

### Arch Linux
```bash
sudo pacman -S --noconfirm \
    base-devel \
    nasm \
    qemu \
    grub \
    xorriso
```

## Quick Build

```bash
# Install dependencies
bash scripts/install_deps.sh

# Build
make build

# Run in QEMU
make qemu
```

## Step-by-Step Build

```bash
# Bootloader
cd bootloader/bios && make && cd ../..

# Kernel
cd kernel && make && cd ..

# Shell
cd shell && make && cd ..

# Create ISO
bash scripts/create_iso.sh
```

## Running

### QEMU
```bash
make qemu
```

### VirtualBox
```bash
virtualbox build/NovaOS.iso
```

## Cleaning

```bash
make clean
```
