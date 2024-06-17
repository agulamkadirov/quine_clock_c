SECTIONS
{
    . = SIZEOF_HEADERS;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
        KEEP(*(.rodata*))
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    .source_code : {
        _s = .;
        KEEP(*(.source_code))
        _e = .;
    }

    /DISCARD/ : { *(.comment) }
}

