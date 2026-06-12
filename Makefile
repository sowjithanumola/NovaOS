# NovaOS Root Makefile

.PHONY: all clean build run qemu vbox help

all: build

build:
	@bash scripts/build.sh

clean:
	@bash scripts/clean.sh

qemu: build
	@bash scripts/run_qemu.sh

vbox: build
	@echo "VirtualBox support coming soon"

help:
	@echo "NovaOS Build Targets:"
	@echo "  make build  - Build entire OS"
	@echo "  make clean  - Clean all build artifacts"
	@echo "  make qemu   - Build and run in QEMU"
	@echo "  make vbox   - Build and run in VirtualBox"
	@echo "  make help   - Display this help"
