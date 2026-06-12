#!/bin/bash

# Create NovaOS Bootable ISO

echo "Creating bootable ISO..."

mkdir -p iso/boot/grub

cat > iso/boot/grub/grub.cfg << 'EOF'
menuentry 'NovaOS' {
    multiboot /boot/kernel.bin
    boot
}
set default=0
set timeout=5
EOF

cp build/kernel.bin iso/boot/
grub-mkrescue -o build/NovaOS.iso iso/

echo "ISO created: build/NovaOS.iso"
