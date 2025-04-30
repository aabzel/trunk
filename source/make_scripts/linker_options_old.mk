#Pass option as an option to the linker.


#--gc-sections  Enable garbage collection of unused input sections.
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
 
LDFLAGS += --specs=nosys.specs
LDFLAGS += --specs=nano.specs
    # Donot use the standard system startup files when linking. 
    # The standard system libraries are used normally, unless -nostdlib, 
    # -nolibc, or -nodefaultlibs is used.
LDFLAGS += -nostartfiles
LDFLAGS += -Wl,-u,_printf_float
#LDFLAGS += -Wl,-u,vfprintf
#LDFLAGS += -Wl,-u,_printf_float
#LDFLAGS += -Wl,-u,_scanf_float
    #$(error LIBC_NANO=$(LIBC_NANO))
    #LINKER_FLAGS += -u _scanf_float
    
    #LINKER_FLAGS += -u _scanf_float
    #LINKER_FLAGS += -u _printf_float
    
   # LIBS += -lc 
   # LIBS += -lc_nano
    
    
    
        
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


#LDFLAGS += $(MICROPROCESSOR)
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += $(LIBDIR)
LDFLAGS += $(LIBS)
# -t
# --trace Print the names of the input files as ld processes them.
LDFLAGS += -t
        #$(error LDFLAGS=$(LDFLAGS))

#Pass option as an option to the linker

#Omit   global symbols defined in discarded sections. 
# LDFLAGS += --strip-discarded  unrecognized command-line option

#When producing an executable file, omit the request for a dynamic linker to be
#used at load-time. This is only meaningful for ELF executables that contain
#dynamic relocations, and usually requires entry point code that is capable of
#processing these relocations.
# LDFLAGS += --no-dynamic-linker unrecognized command-line option 
      
LDFLAGS += -Wl,--cref 
LDFLAGS += -Wl,--gc-sections 
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map 
LDFLAGS += $(LINKER_FLAGS)

ifeq ($(RISC_V), Y)
    ##to suppress it for all standard C
    #LDFLAGS += -fno-builtin-memset

    #LDFLAGS += -fno-builtin
    #LDFLAGS += -Ofast 
    #LDFLAGS +=-g3 

    # Donot use the standard system startup files when linking. 
    # The standard system libraries are used normally, unless �-nostdlib�, �-nolibc�, or �-nodefaultlibs�
    # is used.
#LDFLAGS += -nostartfiles
    
#    LDFLAGS += -nostdlib
    #LDFLAGS += -nostdinc
    #LDFLAGS += -specs=nano.specs -specs=nosys.specs
    #LINKER_FLAGS += -u _printf_float
  #LDFLAGS += -lc 
  #LDFLAGS += -lgcc
  #LDFLAGS += -lnosys 
endif
#LDFLAGS += -Wl,-Tdata,addr

#@echo $(error LDFLAGS=$(LDFLAGS))

#@echo $(error LDFLAGS=$(LDFLAGS))
#@echo $(error LDSCRIPT=$(LDSCRIPT))

