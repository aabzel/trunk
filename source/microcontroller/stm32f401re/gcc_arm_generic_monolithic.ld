/*
**  Author      : aabdev
**
**  Abstract    : Linker script for STM32F401RETx Device with
**                1536KByte FLASH, 320KByte RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 4K;      /* required amount of heap  */
_Min_Stack_Size = 4K; /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
    RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 96K
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 511K
    CALIBRATION_DATA (rx) : ORIGIN = 0x807FC00, LENGTH = 1K
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
   isr_vector_start = .; 
    /*. = ALIGN(4);*/
    KEEP(*(.isr_vector)) /* Startup code */
    /* . = ALIGN(4); */
    isr_vector_end = .; 
  } >FLASH 

  /* . = ABSOLUTE(.); */
/*  . = AT(ADDR(.isr_vector) + SIZEOF(.isr_vector)+64)  AT(ADDR(.isr_vector) + SIZEOF(.isr_vector)+4)*/
  /* . =  (ADDR(.isr_vector) + SIZEOF(.isr_vector));*/
  /* The program code and other data goes into FLASH */
  .text :  
  {
     . = ALIGN(16); 
    text_start = .; 
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH=0x8000198

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH 

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH 

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH 
  
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH 
  
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH 
  
  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  
  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH

   .fill_flash :
   {
        . = ALIGN(4);
         _fill_start = .;  
        /* Fill the remaining space in FLASH with 0xFF */
        FILL(0xFF);
        . = ORIGIN(FLASH) + LENGTH(FLASH) - 1; /* Move location counter to end of FLASH */
        BYTE(0xFF); /* Ensure the very last byte is also filled */
        _fill_end = .;        
   } > FLASH
  
  /* placing my named section at given address: */
  .CalibrationDataSection :
  {
      . = ALIGN(4);
      _calib_data_start = .;  
      KEEP(*(.CalibrationDataSection)) /* keep my variable even if not referenced */
      _calib_data_end = .; 
  } > CALIBRATION_DATA 
  
  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM


  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
    libnosys.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}


