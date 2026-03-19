#Pass option as an option to the linker.
LINKER_GCC_FLAGS += -Xlinker --gc-sections 
LINKER_GCC_FLAGS += -Xlinker --nmagic
# --gc-sections - Enable garbage collection of unused input sections.
# When this option is employed, the linker identifies and removes sections of 
# code or data that are not referenced by any part of the program, thereby 
# reducing the size of the generated binary.
LINKER_GCC_FLAGS += -Wl,--gc-sections
#LINKER_GCC_FLAGS += -Xlinker --print-gc-sections
#LINKER_GCC_FLAGS += -Xlinker --print-map
LINKER_GCC_FLAGS += -Xlinker --print-memory-usage


ifeq ($(LIBC_NOSYS), Y)
    # $(error LIBC_NOSYS=$(LIBC_NOSYS))
    # LINKER_GCC_FLAGS += --specs=nosys.specs
 
    #LIBS_GCC += -lnosys 
endif


ifeq ($(LIBC_NANO), Y)
    # nano.specs defines the system include path and library parameters to 
    # use newlib-nano. The spec file contains replacements for -lc and others 
    # to nano equivalents, e.g. -lc_nano. So using it in conjunction with these 
    # will make gcc still pass nano libaries to the linker.

    #$(error LIBC_NANO=$(LIBC_NANO))
    #LINKER_GCC_FLAGS += -u _scanf_float
    LINKER_GCC_FLAGS += -u _printf_float

    LINKER_GCC_FLAGS += --specs=nosys.specs 
    LINKER_GCC_FLAGS += --specs=nano.specs 
    LINKER_GCC_FLAGS += -nostartfiles 
    LINKER_GCC_FLAGS += -Wl,-u,_printf_float
    #LINKER_GCC_FLAGS += -u _scanf_float

    #LIBS_GCC += -lc 
    #LIBS_GCC += -lc_nano
endif

ifeq ($(LIBC_RDIMON), Y)
    #$(error LIBC_RDIMON=$(LIBC_RDIMON))
    LINKER_GCC_FLAGS += --specs=rdimon.specs
    LINKER_GCC_FLAGS += -u _scanf_float
    LINKER_GCC_FLAGS += -u _printf_float
endif

ifeq ($(LIBC), Y)
    # $(error LIBC=$(LIBC))
    #LIBS_GCC += -lc
endif

ifeq ($(MATH_LIB), Y)
    # $(error MATH_LIB=$(MATH_LIB))
    LIBS_GCC += -lm
endif

LIBDIR += 


LINKER_GCC_FLAGS += $(MICROPROCESSOR)

#-T Use scriptfile as the linker script.
LINKER_GCC_FLAGS += -T$(LDSCRIPT)


# -L Add path searchdir to the list of paths that ld will search for archive 
# libraries and ld control scripts. 
LINKER_GCC_FLAGS += -L$(MCU_CUSTOM_DIR)

LINKER_GCC_FLAGS += $(LIBDIR)
LINKER_GCC_FLAGS += $(LIBS_GCC)
# -t
# --trace Print the names of the input files as ld processes them.
LINKER_GCC_FLAGS += -t

#Pass option as an option to the linker
LINKER_GCC_FLAGS += -Wl,--cref 
LINKER_GCC_FLAGS += -Wl,--gc-sections 
LINKER_GCC_FLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map 
# LINKER_GCC_FLAGS += $(INCDIR)

ifeq ($(RISC_V), Y)
    ##to suppress it for all standard C
    #LINKER_GCC_FLAGS += -fno-builtin-memset

    #LINKER_GCC_FLAGS += -fno-builtin
    #LINKER_GCC_FLAGS += -Ofast 
    #LINKER_GCC_FLAGS +=-g3 

    # Donot use the standard system startup files when linking. The standard system
    # libraries are used normally, unless �-nostdlib�, �-nolibc�, or �-nodefaultlibs�
    # is used.
    LINKER_GCC_FLAGS += -nostartfiles
#    LINKER_GCC_FLAGS += -nostdlib
    #LINKER_GCC_FLAGS += -nostdinc
    #LINKER_GCC_FLAGS += -specs=nano.specs -specs=nosys.specs
     
     
     
    #LINKER_GCC_FLAGS += -lc 
    #LINKER_GCC_FLAGS += -lgcc
    #LINKER_GCC_FLAGS += -lnosys 
    
    
endif
#LINKER_GCC_FLAGS += -Wl,-Tdata,addr

LINKER_GCC_FLAGS += --verbose

LDFLAGS += $(LINKER_GCC_FLAGS)

#@echo $(error LINKER_GCC_FLAGS=$(LINKER_GCC_FLAGS))

#@echo $(error LINKER_GCC_FLAGS=$(LINKER_GCC_FLAGS))
#@echo $(error LDSCRIPT=$(LDSCRIPT))

