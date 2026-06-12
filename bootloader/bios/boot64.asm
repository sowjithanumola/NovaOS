; NovaOS 64-bit Long Mode Entry Point
; This is where the OS fully transitions to 64-bit mode

[BITS 64]

extern kernel_main

boot64_entry:
    ; Stack setup
    mov rsp, 0x7C00
    
    ; Clear segment registers (not needed in long mode)
    xor rax, rax
    
    ; Call kernel_main
    call kernel_main
    
    ; If kernel returns, halt
    cli
    hlt
    jmp $
