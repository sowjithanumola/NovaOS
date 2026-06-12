# NovaOS - A 64-bit Operating System from Scratch

## Overview

NovaOS is a complete 64-bit operating system written in C and Assembly. It boots directly on x86_64 hardware and emulators, featuring a custom bootloader, kernel, device drivers, file system support, and a command-line shell.

## Features

- **Custom Bootloader**: BIOS and UEFI support
- **64-bit Kernel**: Full x86_64 architecture support
- **Memory Management**: Virtual memory, paging, and heap allocation
- **Multitasking**: Process scheduling and context switching
- **Device Drivers**: Keyboard, mouse, storage, display, and networking
- **Shell**: Command-line interface with built-in commands
- **Build System**: Automated compilation with Makefiles
- **Testing**: QEMU and VirtualBox support

## Quick Start

```bash
# Install dependencies
bash scripts/install_deps.sh

# Build NovaOS
make build

# Run in QEMU
make qemu
```

## Project Structure

```
NovaOS/
├── bootloader/          # Boot code (BIOS/UEFI)
├── kernel/              # Kernel core and subsystems
├── shell/               # Command shell
├── scripts/             # Build and test scripts
├── docs/                # Documentation
├── linker/              # Linker scripts
├── config/              # Build configuration
└── Makefile             # Main build file
```

## Building

See [docs/BUILDING.md](docs/BUILDING.md) for comprehensive build instructions.

## Architecture

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for system design overview.

## License

MIT License - See LICENSE file
