#!/bin/bash

# NovaOS Clean Script

echo "Cleaning build artifacts..."

rm -rf build/
find . -name "*.o" -delete
find . -name "*.elf" -delete
find . -name "*.bin" -delete

echo "Clean complete!"
