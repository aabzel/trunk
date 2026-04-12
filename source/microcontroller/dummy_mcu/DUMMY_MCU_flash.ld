/* Entry Point */
ENTRY(Reset_Handler)

__vector_size = 0x0400;
HEAP_SIZE = 4K;
STACK_SIZE = 6K;

/* Specify the memory areas */
MEMORY
{
  
  ITCM_0                  (RW)  : ORIGIN = 0x00000000, LENGTH = 0x8000 /*  */
  ITCM_1                  (RW)  : ORIGIN = 0x00008000, LENGTH = 0x8000 /*  */
  
  PFLASH_0             (RW)  : ORIGIN = 0x01000000, LENGTH = 0x00200000  /* 2MB */
  PFLASH_1             (RW)  : ORIGIN = 0x01200000, LENGTH = 0x00200000  /* 2MB */
  PFLASH_2             (RW)  : ORIGIN = 0x01400000, LENGTH = 0x00200000  /* 2MB */
  PFLASH_3             (RW)  : ORIGIN = 0x01600000, LENGTH = 0x00200000  /* 2MB */
  
  DFLASH                (RW)  : ORIGIN = 0x04000000, LENGTH = 0x00040000  /* 256KB */
  
  NVR                   (RW)  : ORIGIN = 0x04400000, LENGTH = 0x00002000  /* 8KB */
  
  /* DTCM */
  /*DTCM                 (RW)  : ORIGIN = 0x20000000, LENGTH = 0x0001F800    128K - 0x800  */
  /*DTCM_STACK           (RW)  : ORIGIN = 0x2001F800, LENGTH = 0x00000800     0x800  */

  DTCM_STACK           (RW)  : ORIGIN = 0x20000000, LENGTH = 128K    

  
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
    __text_start__ = .;
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
    __text_end__ = .;
  } > PFLASH_0

      .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > PFLASH_0

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > PFLASH_0
    __exidx_end = .;
    





  /* used by the startup to initialize data */
  __data_init_start__ = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
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
        __RamFunc_start__ = .;
       *(.RamFunc)        /* .RamFunc sections */
       *(.RamFunc*)       /* .RamFunc* sections */
        __RamFunc_end__ = .;
 
        . = ALIGN(4);
        /* All data end */

        __data_end__ = .;        /* define a global symbol at data end */
  } >SRAM_0 AT> PFLASH_0
  
   /* ItcmFunctions  section 
     If initialized variables will be placed in this section, the startup code needs 
     to be modified to copy the init-values.  
    ItcmFunctionsBinaryCodeStart = .;
    .ItcmFunctions : AT (ItcmFunctionsBinaryCodeStart)
   */
   
     ItcmFunctionsBinaryCodeStart = LOADADDR(.ItcmFunctions);
     .ItcmFunctions :
    {
        . = ALIGN(4);
        ITCM_FuncStart = .;  /* create a global symbol at ItcmFunctions start */ 
        *(.ItcmFunctions)    /* .ItcmFunctions sections */
        *(.ItcmFunctions*)   /* .ItcmFunctions* sections */

        *(.ITCM_Fun)         /*  .ITCM_Fun sections */
        *(.ITCM_Fun*)        /*  .ITCM_Fun* sections */

        . = ALIGN(4);
        ITCM_FuncEnd = .;    /* create a global symbol at ItcmFunctions end */
    } > ITCM_1 AT> PFLASH_0
  
  



    .bss (NOLOAD):
    {
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
    } > SRAM_0

    .heap :
    {
        . = ALIGN(8);
        __HeapBegin = .;
        _end = .;
        end = _end;
        __end__ = _end;
        . += HEAP_SIZE;
        . = ALIGN(8);
        __Core0_HeapLimit = .;
    } > DTCM_STACK

    .stack_dummy :
    {
        . = ALIGN(8);
        __Core0_StackLimit = .;
        . += STACK_SIZE;
        . = ALIGN(8);
        __Core0_StackTop = .;
    } > DTCM_STACK
    

   .ARM.attributes 0 : { *(.ARM.attributes) }

   ASSERT(__Core0_StackLimit >= __Core0_HeapLimit, "region RAM overflowed with STACK")
    
}

