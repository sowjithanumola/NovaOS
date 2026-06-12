; NovaOS BIOS Bootloader - 16-bit Real Mode
; This is the first code executed by the BIOS
; It transitions the CPU from 16-bit real mode to 32-bit protected mode
; and then to 64-bit long mode

[BITS 16]
[ORG 0x7C00]

; Boot sector entry point
boot_start:
    cli                         ; Clear interrupts
    cld                         ; Clear direction flag
    
    ; Set up segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    
    sti                         ; Enable interrupts
    
    ; Print boot message
    mov si, boot_message
    call print_string_16
    
    ; Load kernel into memory (simple disk read)
    mov ah, 0x02                ; Read sectors
    mov al, 64                  ; Read 64 sectors (32KB)
    mov ch, 0                   ; Cylinder 0
    mov cl, 2                   ; Sector 2
    mov dh, 0                   ; Head 0
    mov dl, 0x80                ; Drive 0 (HDD)
    mov bx, 0x1000             ; Destination address (ES:BX = 0x10000)
    mov es, bx
    xor bx, bx
    int 0x13
    
    jc disk_error
    
    ; Check for A20 line and enable it
    call enable_a20
    
    ; Load GDT
    lgdt [gdt_descriptor]
    
    ; Set protected mode bit in CR0
    mov eax, cr0
    or al, 0x01
    mov cr0, eax
    
    ; Long jump to 32-bit code
    jmp 0x08:boot32_entry
    
boot_message db "NovaOS Bootloader v1.0", 0x0D, 0x0A, "Loading kernel...", 0x0D, 0x0A, 0

print_string_16:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string_16
.done:
    ret

enable_a20:
    ; Try to enable A20 line via keyboard controller
    push ax
    
    ; Wait for keyboard controller ready
    mov al, 0xAD
    out 0x64, al
    mov al, 0xD0
    out 0x64, al
    in al, 0x60
    or al, 0x02
    mov cl, al
    mov al, 0xD1
    out 0x64, al
    mov al, cl
    out 0x60, al
    
    pop ax
    ret

disk_error:
    mov si, error_message
    call print_string_16
    cli
    hlt

error_message db "Disk read error!", 0x0D, 0x0A, 0

; GDT (Global Descriptor Table)
gdt:
    ; Null descriptor
    dq 0x0000000000000000
    
    ; Code descriptor (32-bit)
    dw 0xFFFF                   ; Limit
    dw 0x0000                   ; Base (low)
    db 0x00                     ; Base (mid)
    db 0x9A                     ; Access byte
    db 0xCF                     ; Granularity
    db 0x00                     ; Base (high)
    
    ; Data descriptor (32-bit)
    dw 0xFFFF                   ; Limit
    dw 0x0000                   ; Base (low)
    db 0x00                     ; Base (mid)
    db 0x92                     ; Access byte
    db 0xCF                     ; Granularity
    db 0x00                     ; Base (high)

gdt_descriptor:
    dw gdt_descriptor - gdt - 1
    dd gdt

; Boot signature
times 510 - ($ - $$) db 0
dw 0xAA55
