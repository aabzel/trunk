#Pass option as an option to the linker.
LINKER_FLAGS += -Xlinker --gc-sections 
LINKER_FLAGS += -Xlinker --print-memory-usage


ifeq ($(LIBC_NOSYS), Y)
    # $(error LIBC_NOSYS=$(LIBC_NOSYS))
    # LINKER_FLAGS += --specs=nosys.specs
 
    #LIBS += -lnosys 
endif


ifeq ($(LIBC_NANO), Y)
    # nano.specs defines the system include path and library parameters to 
    # use newlib-nano. The spec file contains replacements for -lc and others 
    # to nano equivalents, e.g. -lc_nano. So using it in conjunction with these 
    # will make gcc still pass nano libaries to the linker.

    #$(error LIBC_NANO=$(LIBC_NANO))
    #LINKER_FLAGS += -u _scanf_float
    #LINKER_FLAGS += -u _printf_float
    
    LINKER_FLAGS += --specs=nosys.specs 
    LINKER_FLAGS += --specs=nano.specs 
    LINKER_FLAGS += -nostartfiles 
    LINKER_FLAGS += -Wl,-u,_printf_float
  
     
    #LIBS += -lc 
    #LIBS += -lc_nano
endif

ifeq ($(LIBC_RDIMON), Y)
    #$(error LIBC_RDIMON=$(LIBC_RDIMON))
    LINKER_FLAGS += --specs=rdimon.specs
    LINKER_FLAGS += -u _scanf_float
    LINKER_FLAGS += -u _printf_float
endif

ifeq ($(LIBC), Y)
    # $(error LIBC=$(LIBC))
    #LIBS += -lc
endif

ifeq ($(MATH_LIB), Y)
    # $(error MATH_LIB=$(MATH_LIB))
    LIBS += -lm
endif

LIBDIR += 


LDFLAGS += $(MICROPROCESSOR)

#-T Use scriptfile as the linker script.
LDFLAGS += -T$(LDSCRIPT)


# -L Add path searchdir to the list of paths that ld will search for archive 
# libraries and ld control scripts. 
LDFLAGS += -L$(MCU_CUSTOM_DIR)

LDFLAGS += $(LIBDIR)
LDFLAGS += $(LIBS)
# -t
# --trace Print the names of the input files as ld processes them.
LDFLAGS += -t

#Pass option as an option to the linker
LDFLAGS += -Wl,--cref 
LDFLAGS += -Wl,--gc-sections 
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map 
LDFLAGS += $(LINKER_FLAGS)
# LDFLAGS += $(INCDIR)

ifeq ($(RISC_V), Y)
    ##to suppress it for all standard C
    #LDFLAGS += -fno-builtin-memset

    #LDFLAGS += -fno-builtin
    #LDFLAGS += -Ofast 
    #LDFLAGS +=-g3 

    # Donot use the standard system startup files when linking. The standard system
    # libraries are used normally, unless -nostdlib, �-nolibc�, or �-nodefaultlibs�
    # is used.
    LDFLAGS += -nostartfiles
    #LDFLAGS += -nostdinc
    #LDFLAGS += -specs=nano.specs -specs=nosys.specs
     
     
     
    #LDFLAGS += -lc 
    #LDFLAGS += -lgcc
    #LDFLAGS += -lnosys 
    
    
endif

ifeq ($(PACK_PROGRAM), Y)
    #remove implementation of such functions as memcpy memset
    # LDFLAGS += -nostdlib
    # LDFLAGS += -lgcc
endif

#LDFLAGS += -Wl,-Tdata,addr

#@echo $(error LDFLAGS=$(LDFLAGS))

#@echo $(error LDFLAGS=$(LDFLAGS))
#@echo $(error LDSCRIPT=$(LDSCRIPT))

