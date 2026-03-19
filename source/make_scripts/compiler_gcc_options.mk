



CFLAGS += -MD

CFLAGS += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))


COMPILE_GCC_OPT += -ffreestanding

#-ffunction-sections Place each function or data item into its own section in the output file if the
#target supports arbitrary sections. The name of the function or the name of
#the data item determines the sectionâ€™s name in the output file.
COMPILE_GCC_OPT += -ffunction-sections

# Place each function or data item into its own section in the output file if the
# target supports arbitrary sections. The name of the function or the name of
# the data item determines the sectionâ€™s name in the output file.
COMPILE_GCC_OPT += -fdata-sections

# The default is ‘-fno-common’, which specifies that the compiler places uninitialized 
# global variables in the BSS section of the object file. 
# This inhibits the merging of tentative definitions by the linker so you get a multiple-definition
# error if the same variable is accidentally defined in more than one compilation unit.
COMPILE_GCC_OPT += -fno-common

# COMPILE_GCC_OPT += -fno-builtin-printf

COMPILE_GCC_OPT += -fno-printf-return-value
#  $(error LITTLE_FS=$(LITTLE_FS))
    
ifneq ($(LITTLE_FS),Y)
    #$(error LITTLE_FS=$(LITTLE_FS))
    
    #Warn whenever a local variable or type declaration shadows another
    #variable, parameter, type, , or instance variable  or whenever a built-in function is shadowed. 
    #If this warning is enabled, it includes also
    #all instances of local shadowing. 
    COMPILE_GCC_OPT += -Werror=shadow
endif

#COMPILE_GCC_OPT += -fpack-struct
COMPILE_GCC_OPT += -fshort-enums


#Make all warnings into errors.
#COMPILE_GCC_OPT += -Werror

COMPILE_GCC_OPT += -fomit-frame-pointer
COMPILE_GCC_OPT += -Werror=return-local-addr


ifneq ($(STM32),Y)
    #COMPILE_GCC_OPT += -Wmissing-prototypes
    COMPILE_GCC_OPT += -Werror=missing-declarations
    COMPILE_GCC_OPT += -Werror=missing-prototypes
    COMPILE_GCC_OPT += -Werror=redundant-decls
endif
COMPILE_GCC_OPT += -Werror=implicit-function-declaration

COMPILE_GCC_OPT += -Wno-nonnull-compare
COMPILE_GCC_OPT += -Wall





# cause too many errors
#COMPILE_GCC_OPT += -Werror=traditional

# cause too many errors


#Perform dead code elimination
COMPILE_GCC_OPT += -fdce

#Perform dead store elimination
COMPILE_GCC_OPT += -fdse

# Print the name of each header file used, in addition to other normal activities.
# Each name is indented to show how deep in the ï¿½#includeï¿½ stack it is. Precompiled
# header files are also printed, even if they are found to be invalid; an invalid
# precompiled header file is printed with ï¿½...xï¿½ and a valid one with ï¿½...!ï¿½ .
# COMPILE_GCC_OPT += -H


ifeq ($(RISC_V),Y)
    COMPILE_GCC_OPT += -Werror=enum-int-mismatch
    # Assert that compilation targets a freestanding environment. This implies
    # -fno-builtin. A freestanding environment is one in which the standard
    # library may not exist, and program startup may not necessarily be at
    # main. The most obvious example is an OS kernel. This is equivalent to
    # ï¿½-fno-hosted
       #COMPILE_GCC_OPT += -ffreestanding
    
    # when you  specify ï¿½-nostdlibï¿½ or ï¿½-nodefaultlibsï¿½ you should usually 
    #  specify ï¿½-lgcc as  well. 
   # COMPILE_GCC_OPT += -nostdlib
    # Do not use the standard system startup files or libraries when linking. 
    # The compiler may generate calls to memcmp, memset, memcpy and memmove
    COMPILE_GCC_OPT += -lgcc
    
    
    # Do not use the C library or system libraries tightly coupled with it 
    # when link ing. 
    #COMPILE_GCC_OPT += -nolibc
    

    # Donot use the standard system startup files when linking. 
    # The standard system libraries are used normally, unless ï¿½-nostdlibï¿½, 
    # ï¿½-nolibcï¿½, or ï¿½-nodefaultlibsï¿½ is used.
    COMPILE_GCC_OPT += -nostartfiles
    COMPILE_GCC_OPT += -Wno-int-conversion
else
    #COMPILE_GCC_OPT += -Werror=int-conversion
    COMPILE_GCC_OPT += -Werror=address-of-packed-member
endif

ifeq ($(EHAL),Y)
   #COMPILE_GCC_OPT += -Wmissing-field-initializers
   
       #LDFLAGS += -lc # big binary
       
    
else
   COMPILE_GCC_OPT += -Werror=missing-field-initializers
 # COMPILE_GCC_OPT += -Werror=implicit-function-declaration
   ifneq ($(EHAL_MCAL),Y)
        COMPILE_GCC_OPT += -Werror=unused-but-set-variable
        COMPILE_GCC_OPT += -Werror=unused-variable
    endif
endif


ifeq ($(DEBUG), Y)
    # Reduce compilation time and make debugging produce the expected results.
    OPTIMIZATION = -O0
    
    OPTIMIZATION = -fno-builtin
    # $(error DEBUG=$(DEBUG))

    #Request debugging information and also use level to specify how much information.
    # -g3 Level 3 includes extra information, such as all the macro definitions present in
    # the program. Some debuggers support macro expansion when you use ï¿½-g3ï¿½.
    COMPILE_GCC_OPT += -g3 

    # Produce debugging information for use by GDB. This means to use the most
    # expressive format available (DWARF, stabs, or the native format if neither of
    # those are supported), including GDB extensions if at all possible.
    #COMPILE_GCC_OPT += -ggdb 
    
    #Produce debugging information in DWARF format (if that is supported). 
    #COMPILE_GCC_OPT += -gdwarf-2
else
    # Optimize for size. ï¿½-Osï¿½ enables all ï¿½-O2ï¿½ optimizations except those that often
    # increase code size: -falign-functions  -falign-jumps -falign-labels  -falign-loops
    # -fprefetch-loop-arrays  -freorder-blocks-algorithm=stc It also enables ï¿½-finline-functionsï¿½
    # , causes the compiler to tune for code size rather than execution speed, and 
    # performs further optimizations designed to reduce code size.
    OPTIMIZATION = -Os
endif

ifeq ($(HI_PERF), Y)
    OPTIMIZATION = -Ofast
endif

ifeq ($(PACK_PROGRAM), Y)
    # $(error PACK_PROGRAM=$(PACK_PROGRAM))
     #OPTIMIZATION = -Os
     OPTIMIZATION = -Os

    #When compiling with -flto, no callgraph information is output along with
    #the object file.
    #This option runs the standard link-time optimizer.
    #When invoked with source code, it generates GIMPLE (one of GCCs internal representations) and writes
    #it to special ELF sections in the object file.
    # When the object files are linked together, all the function bodies are read 
    # from these ELF sections and instantiated as if they had been part of the same translation unit.
      COMPILE_GCC_OPT += -flto
      #COMPILE_GCC_OPT += -flto-report
endif

# order matter
include $(WORKSPACE_LOC)/make_scripts/compiler_warning.mk
include $(WORKSPACE_LOC)/make_scripts/compiler_options_for_c_code.mk
include $(WORKSPACE_LOC)/make_scripts/compiler_errors.mk
include $(WORKSPACE_LOC)/make_scripts/compiler_warning_mute.mk

#COMPILE_GCC_OPT += -Wformat-overflow=1
COMPILE_GCC_OPT += $(MICROPROCESSOR)  
COMPILE_GCC_OPT += $(OPTIMIZATION)
COMPILE_GCC_OPT += $(CSTANDARD)
# Generate dependency information
COMPILE_GCC_OPT += -MMD -MP -MF"$(@:%.o=%.d)"

CFLAGS += $(MCAL_OPT)

# $(error CFLAGS=$(CFLAGS))

