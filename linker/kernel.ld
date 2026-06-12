ENTRY(kernel_entry)

SECTIONS
{
    . = 0x100000;
    
    .text :
    {
        *(.text .text.*)
        . = ALIGN(4096);
    }
    
    .data :
    {
        *(.data .data.*)
        . = ALIGN(4096);
    }
    
    .bss :
    {
        *(.bss .bss.*)
        . = ALIGN(4096);
    }
    
    .rodata :
    {
        *(.rodata .rodata.*)
        . = ALIGN(4096);
    }
    
    /DISCARD/ :
    {
        *(.note*)
        *(.comment*)
        *(.eh_frame*)
    }
}
