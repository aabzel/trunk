/* Entry Point */
ENTRY(Reset_Handler)

__vector_size = 0x0400;
HEAP_SIZE = 0x400;
STACK_SIZE = 0x400;

/* Specify the memory areas */
MEMORY
{
  
  ITCM                  (RW)  : ORIGIN = 0x00000000, LENGTH = 0x00010000 /* 64KB */
  
  PFLASH_0             (RW)  : ORIGIN = 0x01000000, LENGTH = 0x00200000  /* 2MB */
  PFLASH_1             (RW)  : ORIGIN = 0x01200000, LENGTH = 0x00200000  /* 2MB */
  PFLASH_2             (RW)  : ORIGIN = 0x01400000, LENGTH = 0x00200000  /* 2MB */
  PFLASH_3             (RW)  : ORIGIN = 0x01600000, LENGTH = 0x00200000  /* 2MB */
  
  DFLASH                (RW)  : ORIGIN = 0x04000000, LENGTH = 0x00040000  /* 256KB */
  
  NVR                   (RW)  : ORIGIN = 0x04400000, LENGTH = 0x00002000  /* 8KB */
  
  /* DTCM */
  DTCM                 (RW)  : ORIGIN = 0x20000000, LENGTH = 0x0001F800    /* 128K - 0x800  */
  DTCM_STACK           (RW)  : ORIGIN = 0x2001F800, LENGTH = 0x00000800    /* 0x800  */
  
  SRAM_0               (RW)  : ORIGIN = 0x21000000, LENGTH = 0x00020000  /* 128KB */
  SRAM_1               (RW)  : ORIGIN = 0x21020000, LENGTH = 0x00020000  /* 128KB */
  SRAM_2               (RW)  : ORIGIN = 0x21040000, LENGTH = 0x00040000  /* 256KB */
  
}

/* Define output sections */
SECTIONS
{

  /* The program code and other data goes into internal flash */
  .text :
  {
    . = ALIGN(1024); /* VTOR must be align to 1K */
    __interrupts_start__ = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    __interrupts_end__ = .;
    . = ALIGN(4);
        
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.init)                 /* section used in crti.o files */
    *(.fini)                 /* section used in crti.o files */
    *(.eh_frame)             /* section used in crtbegin.o files */
    . = ALIGN(4);
  } > SRAM_0

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM_0

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > SRAM_0
    __exidx_end = .;

    __data_init_start__ = .;
 
    .data : AT (__data_init_start__)
    {
        __data_start__ = .;
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > SRAM_1

    .bss (NOLOAD):
    {
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
    } > SRAM_1



    .heap :
    {
        . = ALIGN(8);
        __HeapBegin = .;
        _end = .;
        end = _end;
        . += HEAP_SIZE;
        . = ALIGN(8);
        __HeapLimit = .;
    } > DTCM_STACK

    .stack_dummy :
    {
        . = ALIGN(8);
        __StackLimit = .;
        . += STACK_SIZE;
        . = ALIGN(8);
        __StackTop = .;
    } > DTCM_STACK


  .ARM.attributes 0 : { *(.ARM.attributes) }

  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with STACK")
    
}

