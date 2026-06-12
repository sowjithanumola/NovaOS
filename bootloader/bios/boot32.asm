; NovaOS 32-bit Protected Mode Code
; This code continues from the 16-bit bootloader
; It sets up the stack, enables paging, and transitions to 64-bit mode

[BITS 32]

boot32_entry:
    ; Set up stack
    mov esp, 0x7C00
    
    ; Set up segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    
    ; Check for CPUID support
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 0x00200000
    push eax
    popfd
    pushfd
    pop eax
    xor eax, ecx
    test eax, 0x00200000
    jz no_cpuid
    
    ; Check for 64-bit support
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jl no_64bit
    
    mov eax, 0x80000001
    cpuid
    test edx, 0x20000000        ; Check for LM bit (Long Mode)
    jz no_64bit
    
    ; Set up page tables for 64-bit
    call setup_paging_32
    
    ; Enable PAE (Physical Address Extension)
    mov eax, cr4
    or eax, 0x00000020
    mov cr4, eax
    
    ; Set EFER.LME (Long Mode Enable)
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x00000100
    wrmsr
    
    ; Load page tables
    mov eax, page_table_l4
    mov cr3, eax
    
    ; Enable paging
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    
    ; Load 64-bit GDT
    lgdt [gdt64_descriptor]
    
    ; Long jump to 64-bit code
    jmp 0x08:boot64_entry
    
no_cpuid:
    mov si, no_cpuid_msg
    call print_string_32
    cli
    hlt

no_64bit:
    mov si, no_64bit_msg
    call print_string_32
    cli
    hlt

setup_paging_32:
    ; Map first 2MB with 2MB pages
    ; This is simplified - in production, use full 4-level paging
    
    ; Clear page tables
    mov edi, page_table_l4
    xor eax, eax
    mov ecx, 4096 * 4
    rep stosd
    
    ; Set up L4 table
    mov eax, page_table_l3 | 0x03
    mov [page_table_l4], eax
    
    ; Set up L3 table
    mov eax, page_table_l2 | 0x03
    mov [page_table_l3], eax
    
    ; Set up L2 table (identity map first 2MB)
    mov eax, 0x00000183        ; 2MB page, present, writable
    mov ecx, 512
    mov edi, page_table_l2
.map_pages:
    stosd
    add eax, 0x00200000        ; Next 2MB
    loop .map_pages
    
    ret

print_string_32:
    mov eax, [esi]
    test eax, eax
    jz .done
    
    ; Simple text output (VGA)
    mov dword [0xB8000], eax
    add esi, 4
    jmp print_string_32
.done:
    ret

no_cpuid_msg db "CPUID not supported", 0
no_64bit_msg db "64-bit not supported", 0

; 64-bit GDT
align 8
gdt64:
    dq 0x0000000000000000       ; Null descriptor
    
    dq 0x00209a0000000000       ; 64-bit code descriptor
    dq 0x0000920000000000       ; 64-bit data descriptor

gdt64_descriptor:
    dw gdt64_descriptor - gdt64 - 1
    dq gdt64

; Page table structures
align 4096
page_table_l4:
    times 512 dq 0

align 4096
page_table_l3:
    times 512 dq 0

align 4096
page_table_l2:
    times 512 dq 0
