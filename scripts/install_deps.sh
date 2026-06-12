#!/bin/bash

# Install NovaOS dependencies

echo "Installing NovaOS build dependencies..."

if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    echo "Error: Could not detect OS"
    exit 1
fi

case $OS in
    ubuntu|debian)
        echo "Ubuntu/Debian detected."
        sudo apt-get update
        sudo apt-get install -y \
            build-essential \
            nasm \
            gcc-x86-64-linux-gnu \
            binutils-x86-64-linux-gnu \
            qemu-system-x86 \
            grub-pc-bin \
            xorriso
        ;;
    fedora)
        echo "Fedora detected."
        sudo dnf install -y \
            gcc \
            nasm \
            binutils \
            qemu-system-x86 \
            grub2-tools \
            xorriso
        ;;
    arch)
        echo "Arch Linux detected."
        sudo pacman -S --noconfirm \
            base-devel \
            nasm \
            qemu \
            grub \
            xorriso
        ;;
    *)
        echo "Unsupported OS: $OS"
        exit 1
        ;;
esac

echo "Dependencies installed!"
