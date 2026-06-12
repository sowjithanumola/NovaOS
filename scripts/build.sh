#!/bin/bash

# NovaOS Build Script

set -e

GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}      NovaOS Build System${NC}"
echo -e "${BLUE}========================================${NC}\n"

echo -e "${BLUE}[*] Building bootloader...${NC}"
cd bootloader/bios
make
cd ../..
echo -e "${GREEN}[✓] Bootloader built${NC}\n"

echo -e "${BLUE}[*] Building kernel...${NC}"
cd kernel
make
cd ..
echo -e "${GREEN}[✓] Kernel built${NC}\n"

echo -e "${BLUE}[*] Building shell...${NC}"
cd shell
make
cd ..
echo -e "${GREEN}[✓] Shell built${NC}\n"

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}      Build Complete!${NC}"
echo -e "${GREEN}========================================${NC}\n"
