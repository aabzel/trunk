$(info CORTEX_SELECT_MK_INC=$(CORTEX_SELECT_MK_INC) )
ifneq ($(CORTEX_SELECT_MK_INC),Y)
    CORTEX_SELECT_MK_INC=Y

    CORTEX_SEL_DIR = $(CORE_DIR)/cortex_m4
    INCDIR += -I$(CORTEX_SEL_DIR)
    # $(error CORTEX_SEL_DIR=$(CORTEX_SEL_DIR))

    MICROCONTROLLER=Y
    SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_driver.c
    MCAL_OPT += -DHAS_ARM
    MCAL_OPT += -DHAS_CORTEX_M4
    MCAL_OPT += -DHAS_CORTEX_M
    
    ifeq ($(DIAG),Y)
        ifeq ($(CORTEX_M4_DIAG),Y)
            MCAL_OPT += -DHAS_CORTEX_M4_DIAG
            SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CORTEX_M4_COMMANDS),Y)
            MCAL_OPT += -DHAS_CORTEX_M4_COMMANDS
            SOURCES_C += $(CORTEX_SEL_DIR)/cortex_m4_commands.c
        endif
    endif

    MICROPROCESSOR += -mcpu=cortex-m4 
    MICROPROCESSOR += -march=armv7e-m


    # Do not use the standard system startup files or libraries when linking. No
    # startup files and only the libraries you specify are passed to the linker, and
    # options specifying linkage of the system libraries, such as ‘-static-libgcc’ or
    # ‘-shared-libgcc’, are ignored.
    # The compiler may generate calls to memcmp, memset, memcpy and memmove.
    # These entries are usually resolved by entries in libc. These entry points should
    # be supplied through some other mechanism when this option is specified.
    # One of the standard libraries bypassed by ‘-nostdlib’ and ‘-nodefaultlibs’
    # is ‘libgcc.a’, a library of internal subroutines which GCC uses to overcome
    # shortcomings of particular machines, or special needs for some languages. 
    # In most cases, you need ‘libgcc.a’ even when you want to avoid other standard libraries. 
    # In other words, when you specify ‘-nostdlib’ or ‘-nodefaultlibs’ you should usually specify ‘-lgcc’ as
    # well. This ensures that you have no unresolved references to internal GCC
    # library subroutines. (An example of such an internal subroutine is __main,
    # used to ensure C++ constructors are called; see Section “collect2” in GNU
    # Compiler Collection (GCC) Internals.)
        # MICROPROCESSOR += -nostdlib

    # Do not use the standard system startup files when linking. The standard system
    # libraries are used normally, unless ‘-nostdlib’, ‘-nolibc’, or ‘-nodefaultlibs’
    # is used.
     #MICROPROCESSOR += -nostartfiles


    # Assert that compilation targets a freestanding environment. This implies
    # ‘-fno-builtin’. A freestanding environment is one in which the standard
    # library may not exist, and program startup may not necessarily be at
    # main. The most obvious example is an OS kernel. This is equivalent to
    # ‘-fno-hosted’.
    MICROPROCESSOR += -ffreestanding
    MICROPROCESSOR += -mthumb
    
    ifeq ($(MPU),Y)
        MCAL_OPT += -D__MPU_PRESENT=1
    endif

    ifeq ($(FPU),Y)
        MCAL_OPT += -DHAS_FPU
        #MCAL_OPT += -D__FPU_PRESENT=1
        #MCAL_OPT += -D__FPU_USED=1
        MICROPROCESSOR += -mfloat-abi=hard
        MICROPROCESSOR += -mfpu=fpv4-sp-d16
    else
        MICROPROCESSOR += -mfloat-abi=soft
    endif

endif