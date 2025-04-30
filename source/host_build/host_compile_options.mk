
COMPILE_OPT += -Werror=return-local-addr
COMPILE_OPT += -Werror=missing-declarations
COMPILE_OPT += -Werror=missing-prototypes

COMPILE_OPT += -Werror=shadow

#-ffunction-sections Place each function or data item into its own section in the output file if the
#target supports arbitrary sections. The name of the function or the name of
#the data item determines the section’s name in the output file.
COMPILE_OPT += -ffunction-sections


# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
COMPILE_OPT += -g

#Generate code for 32-bit ABI
COMPILE_OPT += -m32

COMPILE_OPT += -std=c11  
COMPILE_OPT  += -fshort-enums
#COMPILE_OPT += -Og
COMPILE_OPT  += -O0
COMPILE_OPT  += -Wall
#COMPILE_OPT  += -Wrestrict
#COMPILE_OPT  +=-pedantic
#COMPILE_OPT += -ftime-report

COMPILE_OPT += -time
#OPT += -Wrestrict
#COMPILE_OPT += -Wall
COMPILE_OPT += -Werror=switch
COMPILE_OPT += -Werror=implicit-function-declaration  # due to strdup
COMPILE_OPT += -Werror=div-by-zero
COMPILE_OPT += -Werror=shift-negative-value
COMPILE_OPT += -Werror=uninitialized
COMPILE_OPT += -Werror=empty-body
COMPILE_OPT += -Werror=unused-but-set-variable
COMPILE_OPT += -Werror=unused-variable
COMPILE_OPT += -Werror=unused-function
COMPILE_OPT += -Werror=incompatible-pointer-types
COMPILE_OPT += -Werror=return-type
COMPILE_OPT += -Werror=enum-compare
#COMPILE_OPT += -Werror=no-restrict

#COMPILE_OPT += -Werror=restrict
COMPILE_OPT += -Wno-format-extra-args
COMPILE_OPT += -Wno-pointer-sign
COMPILE_OPT += -Wno-cpp #TODO temp
COMPILE_OPT += -Wno-discarded-qualifiers
#Perform dead code elimination
COMPILE_OPT += -fdce

#Perform dead store elimination
COMPILE_OPT += -fdse

COMPILE_OPT += -fmax-errors=7
ifeq ($(HI_PERF), Y)
    OPTIMIZATION = -Ofast
endif

ifeq ($(PACK_PROGRAM), Y)
    # $(error PACK_PROGRAM=$(PACK_PROGRAM))
    OPTIMIZATION = -Os
endif

ifneq ($(PC), Y)
    COMPILE_OPT += -Werror=enum-int-mismatch
    COMPILE_OPT += -Werror=duplicate-decl-specifier
endif