#!/bin/bash

# Run NovaOS in QEMU

QEMU_CMD="qemu-system-x86_64"
ISO_PATH="build/NovaOS.iso"

echo "Starting QEMU..."

$QEMU_CMD \
    -m 512 \
    -cdrom "$ISO_PATH" \
    -boot d \
    -serial stdio \
    -d guest_errors
