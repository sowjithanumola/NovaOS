# NovaOS Architecture

## System Overview

NovaOS is a 64-bit operating system with a modular architecture:

```
┌─────────────────────────────────┐
│   User Applications (Ring 3)    │
├─────────────────────────────────┤
│   System Call Interface         │
├─────────────────────────────────┤
│      KERNEL (Ring 0)            │
│  ┌──────────────────────────┐   │
│  │ Process Scheduler        │   │
│  │ Memory Management        │   │
│  │ Device Drivers           │   │
│  │ File System              │   │
│  └──────────────────────────┘   │
├─────────────────────────────────┤
│   Bootloader (Real Mode)        │
└─────────────────────────────────┘
```

## Boot Sequence

1. **BIOS Bootloader** - 16-bit real mode
2. **Protected Mode** - 32-bit transition
3. **Long Mode** - 64-bit entry
4. **Kernel Init** - Core systems

## Memory Layout

- **Kernel Space**: 0xFFFF800000000000
- **Heap**: 0xFFFF800000100000
- **Stack**: 0xFFFF800000200000

## Privilege Levels

- **Ring 0**: Kernel
- **Ring 3**: User Applications

## Process Management

- Round-robin scheduling
- Priority levels
- Context switching

## Memory Management

- 4KB page size
- 4-level page tables
- Heap allocator with coalescing
