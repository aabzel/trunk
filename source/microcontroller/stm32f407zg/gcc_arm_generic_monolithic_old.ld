
/*
  Abstract    : Linker script for STM32F407ZGTx series
                1024Kbytes FLASH and 192 Kbytes RAM
                Set heap size, stack size and stack location according
                to application requirements.
                Set memory bank area and size if external memory is used.
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);    /* end of CCMRAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size  = 4K;      /* required amount of heap  */
_Min_Stack_Size = 15K;      /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
RAM (xrw)    : ORIGIN = 0x20000000, LENGTH = 128K
CCMRAM (xrw) : ORIGIN = 0x10000000, LENGTH = 64K
FLASH1 (rx)    : ORIGIN = 0x08000000, LENGTH = 1K
CONFIGURATION_DATA (rx)    : ORIGIN = 0x08000400, LENGTH = 31K
NVRAM (rx)     : ORIGIN = 0x08008000, LENGTH = 32K
FLASH2 (rx)    : ORIGIN = 0x08010000, LENGTH = 690K
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    __isr_vector_start__ = . ;
    KEEP(*(.isr_vector))          /* Startup code */
    __isr_vector_end__ = . ;
     FILL(0xFF); 
    . = ALIGN(4);
  } >FLASH1

    /*We will change content of ConfigurationData with TunerPRO program*/
    .ConfigurationData :
    {
        __configuration_data_section_start__ = .;
        KEEP(*(.ConfigurationData))
        __configuration_data_section_end__ = .;
        FILL(0xFF);
        . = ORIGIN(CONFIGURATION_DATA) + LENGTH(CONFIGURATION_DATA); 
    } >CONFIGURATION_DATA

   /* placing my named section at given address: */
  .NvRam  : {
      . = ALIGN(4);
      _nvram_start = .;  

      KEEP(*(.NvRam))
      KEEP(*(.NvRam.*))
     FILL(0xFF);
      . = ORIGIN(NVRAM) + LENGTH(NVRAM); /* Move location counter to end of FLASH */
      _nvram_end = .; 
  } > NVRAM

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    start_text = .;        /* define a global symbols at start of code */
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
         FILL(0xFF); 
  } >FLASH2

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
         FILL(0xFF); 
  } >FLASH2

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH2
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
         FILL(0xFF); 
  } >FLASH2

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
         FILL(0xFF); 
  } >FLASH2

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
         FILL(0xFF); 
  } >FLASH2

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
         FILL(0xFF); 
  } >FLASH2

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    __RamFunc_start__ = .; 
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */
    __RamFunc_end__ = .;
       
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
         FILL(0xFF); 
  } >RAM AT> FLASH2


   /* RamFunctions  section 
     If initialized variables will be placed in this section,
     the startup code needs to be modified to copy the init-values.  
   */
    RamFunctionsBinaryCodeStart = LOADADDR(.RamFunctions);
    .RamFunctions :
    {
        . = ALIGN(4);
        RamFuncStart = .;  /* create a global symbol at RamFunctions start */ 
        *(.RamFunctions)   /* .RamFunctions sections */
        *(.RamFunctions*)  /* .RamFunctions* sections */
        
        *(.Ram_Fun)       /*  .CCMRamFunc sections */
        *(.Ram_Fun*)      /*  .CCMRamFunc* sections */
         FILL(0xFF); 
        . = ALIGN(4);
        RamFuncEnd = .;    /* create a global symbol at RamFunctions end */
    } >RAM AT> FLASH2

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
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    
    __Core0_StackLimit = .;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
    __Core0_StackTop = . ;
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


