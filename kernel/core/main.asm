; NovaOS Kernel Entry Point (64-bit)
; This is the first code executed after the bootloader
; It initializes the kernel core systems

[BITS 64]
[ORG 0x100000]

extern kmain

section .text
global kernel_entry

kernel_entry:
    ; Disable interrupts
    cli
    
    ; Set up kernel stack
    mov rsp, kernel_stack_top
    mov rbp, rsp
    
    ; Call kernel main function
    call kmain
    
    ; Halt if kernel returns
    cli
    hlt
    jmp $

section .data
align 16
kernel_stack:
    times 65536 db 0
kernel_stack_top:
