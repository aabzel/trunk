#COMPILE_OPT += -fpack-struct
COMPILE_OPT += -fshort-enums


#Make all warnings into errors.
#COMPILE_OPT += -Werror

COMPILE_OPT += -fomit-frame-pointer
COMPILE_OPT += -Werror=return-local-addr


ifneq ($(STM32),Y)
    #COMPILE_OPT += -Wmissing-prototypes
    COMPILE_OPT += -Werror=missing-declarations
    COMPILE_OPT += -Werror=missing-prototypes
    COMPILE_OPT += -Werror=redundant-decls
    #COMPILE_OPT += -Werror=implicit-function-declaration
endif

COMPILE_OPT += -Werror=shadow

COMPILE_OPT += -Wno-nonnull-compare
COMPILE_OPT += -Wall

#Place each function or data item into its own section in the output file if the
#target supports arbitrary sections. The name of the function or the name of
#the data item determines the section’s name in the output file.
COMPILE_OPT += -fdata-sections

#-ffunction-sections Place each function or data item into its own section in the output file if the
#target supports arbitrary sections. The name of the function or the name of
#the data item determines the section’s name in the output file.
COMPILE_OPT += -ffunction-sections

COMPILE_OPT += -Werror=address
COMPILE_OPT += -Werror=switch
COMPILE_OPT += -Werror=array-bounds=1
COMPILE_OPT += -Werror=comment
COMPILE_OPT += -Werror=div-by-zero
COMPILE_OPT += -Werror=duplicated-cond
COMPILE_OPT += -Werror=shift-negative-value
COMPILE_OPT += -Werror=duplicate-decl-specifier
COMPILE_OPT += -Werror=enum-compare
COMPILE_OPT += -Werror=uninitialized
COMPILE_OPT += -Werror=empty-body
COMPILE_OPT += -Werror=unused-but-set-parameter
COMPILE_OPT += -Werror=unused-but-set-variable
COMPILE_OPT += -Werror=float-equal
COMPILE_OPT += -Werror=logical-op
COMPILE_OPT += -Werror=implicit-int
COMPILE_OPT += -Werror=incompatible-pointer-types
COMPILE_OPT += -Werror=old-style-declaration
COMPILE_OPT += -Werror=maybe-uninitialized
COMPILE_OPT += -Werror=sizeof-pointer-div
COMPILE_OPT += -Werror=misleading-indentation
COMPILE_OPT += -Werror=missing-parameter-type
COMPILE_OPT += -Werror=overflow
COMPILE_OPT += -Werror=parentheses
COMPILE_OPT += -Werror=pointer-sign
COMPILE_OPT += -Werror=return-type
COMPILE_OPT += -Werror=format
COMPILE_OPT += -Werror=shift-count-overflow
COMPILE_OPT += -Werror=strict-prototypes
COMPILE_OPT += -Werror=unused-but-set-variable
COMPILE_OPT += -Werror=unused-function
COMPILE_OPT += -Werror=unused-variable
#COMPILE_OPT += -Werror=discarded-qualifiers
#COMPILE_OPT += -Werror=type-limits
#COMPILE_OPT += -Werror=override-init
#COMPILE_OPT += -Werror=duplicate-decl-specifier

#COMPILE_OPT += -Werror=int-conversion
COMPILE_OPT += -Wno-stringop-truncation
COMPILE_OPT += -Wno-format-truncation
COMPILE_OPT += -Wno-restrict
COMPILE_OPT += -Wno-format
COMPILE_OPT += -Wno-cpp #TODO temp
#COMPILE_OPT += -Wno-discarded-qualifiers


# cause too many errors
#COMPILE_OPT += -Werror=traditional

# cause too many errors



#Perform dead code elimination
COMPILE_OPT += -fdce

#Perform dead store elimination
COMPILE_OPT += -fdse


# Print the name of each header file used, in addition to other normal activities.
# Each name is indented to show how deep in the �#include� stack it is. Precompiled
# header files are also printed, even if they are found to be invalid; an invalid
# precompiled header file is printed with �...x� and a valid one with �...!� .
# COMPILE_OPT += -H

COMPILE_OPT += -fmax-errors=7
COMPILE_OPT += -fmessage-length=0
COMPILE_OPT += -fsigned-char
COMPILE_OPT += -fno-common
COMPILE_OPT += -fstack-usage
COMPILE_OPT += -fzero-initialized-in-bss
COMPILE_OPT += -finline-small-functions
COMPILE_OPT += -finline-functions

ifeq ($(RISC_V),Y)
    COMPILE_OPT += -Werror=enum-int-mismatch
 
    
    # Assert that compilation targets a freestanding environment. This implies
    # �-fno-builtin�. A freestanding environment is one in which the standard
    # library may not exist, and program startup may not necessarily be at
    # main. The most obvious example is an OS kernel. This is equivalent to
    # �-fno-hosted�.
       #COMPILE_OPT += -ffreestanding
    
    # when you  specify �-nostdlib� or �-nodefaultlibs� you should usually 
    #  specify �-lgcc� as  well. 
   # COMPILE_OPT += -nostdlib
    # Do not use the standard system startup files or libraries when linking. 
    # The compiler may generate calls to memcmp, memset, memcpy and memmove
    COMPILE_OPT += -lgcc
    
    
    # Do not use the C library or system libraries tightly coupled with it 
    # when link ing. 
    #COMPILE_OPT += -nolibc
    

    # Donot use the standard system startup files when linking. 
    # The standard system libraries are used normally, unless �-nostdlib�, 
    # �-nolibc�, or �-nodefaultlibs� is used.
    COMPILE_OPT += -nostartfiles
    COMPILE_OPT += -Wno-int-conversion
else
    #COMPILE_OPT += -Werror=int-conversion
    COMPILE_OPT += -Werror=address-of-packed-member
endif

ifeq ($(EHAL),Y)
   #COMPILE_OPT += -Wmissing-field-initializers
   
       #LDFLAGS += -lc # big binary
       
    
else
   COMPILE_OPT += -Werror=missing-field-initializers
 # COMPILE_OPT += -Werror=implicit-function-declaration
   ifneq ($(EHAL_MCAL),Y)
        COMPILE_OPT += -Werror=unused-but-set-variable
        COMPILE_OPT += -Werror=unused-variable
    endif
endif

ifeq ($(DEBUG), Y)
    # Reduce compilation time and make debugging produce the expected results.
    #OPTIMIZATION = -Og # LED will not work with that flag
    OPTIMIZATION = -O0

    # $(error DEBUG=$(DEBUG))

    #Request debugging information and also use level to specify how much information.
    # -g3 Level 3 includes extra information, such as all the macro definitions present in
    # the program. Some debuggers support macro expansion when you use �-g3�.
    COMPILE_OPT += -g3 

    # Produce debugging information for use by GDB. This means to use the most
    # expressive format available (DWARF, stabs, or the native format if neither of
    # those are supported), including GDB extensions if at all possible.
    #COMPILE_OPT += -ggdb 
    
    #Produce debugging information in DWARF format (if that is supported). 
    #COMPILE_OPT += -gdwarf-2
else
    # Optimize for size. �-Os� enables all �-O2� optimizations except those that often
    # increase code size: -falign-functions  -falign-jumps -falign-labels  -falign-loops
    # -fprefetch-loop-arrays  -freorder-blocks-algorithm=stc It also enables �-finline-functions�
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
      COMPILE_OPT += -flto
      #COMPILE_OPT += -flto-report
endif

#COMPILE_OPT += -Wformat-overflow=1
COMPILE_OPT += $(MICROPROCESSOR)  
COMPILE_OPT += $(OPTIMIZATION)
COMPILE_OPT += $(CSTANDARD)
COMPILE_OPT += $(INCDIR)
# Generate dependency information
COMPILE_OPT += -MMD -MP -MF"$(@:%.o=%.d)"

CFLAGS += $(OPT)
CFLAGS += $(COMPILE_OPT)
