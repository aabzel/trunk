
PYTHON_BIN=python.exe
SORTER_TOOL=C:/cygwin64/bin/sort.exe

#COMPILE_OPT += $(COMPILE_GCC_OPT)

ifeq ($(ARM), Y)
    #  arm-none-eabi-gcc.exe
    # C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin\arm-none-eabi-gcc.exe
    PREFIX = arm-none-eabi-
endif

ifeq ($(RISC_V), Y)
   #PREFIX = riscv64-unknown-elf-
   PREFIX = riscv-none-elf-
   # INCDIR += -IC:/riscv-gcc/riscv64-unknown-elf/lib/rv32im/ilp32
   # INCDIR += -IC:/riscv-gcc/riscv64-unknown-elf/lib/rv32i/ilp32
   # INCDIR += -IC:/riscv-gcc/riscv64-unknown-elf/lib/rv32imc/ilp32
   # INCDIR += -IC:/riscv-gcc/riscv64-unknown-elf/lib
endif

# binaries
#GCC_PATH="C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin"
$(info GCC_PATH=$(GCC_PATH))


# The gcc compiler bin path can be either defined in make command via GCC_PATH
# variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
    $(info WithPath)
    PREPROCESSOR_TOOL =$(GCC_PATH)/$(PREFIX)cpp
    CC = $(GCC_PATH)/$(PREFIX)gcc
    CPP = $(GCC_PATH)/$(PREFIX)g++
    AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
    CP = $(GCC_PATH)/$(PREFIX)objcopy
    SZ = $(GCC_PATH)/$(PREFIX)size
else
    $(info WithOutPath)
    PREPROCESSOR_TOOL = $(PREFIX)cpp
    CC = $(PREFIX)gcc
    CPP = $(PREFIX)g++
    AS = $(PREFIX)gcc -x assembler-with-cpp
    CP = $(PREFIX)objcopy
    SZ = $(PREFIX)size
endif

OBJCOPY_OPT=

# Remove any section matching sectionpattern from the output file. 
# This option may be given more than once. 
# Note that using this option inappropriately may make the output file unusable.
# Wildcard characters are accepted in sectionpattern. Using both the -j and -R options 
# together results in undefined behaviour.
OBJCOPY_OPT +=-R RAM

# Fill gaps between sections with val. This operation applies to the load address (LMA) of the sections. 
# It is done by increasing the size of the section with the lower address, and filling
# in the extra space created with val.
OBJCOPY_OPT +=--gap-fill 0xFF

#Do not copy relocation and symbol information from the source file. Also deletes debug sections.
OBJCOPY_OPT +=-S

HEX = $(CP) -O ihex $(OBJCOPY_OPT)  
BIN = $(CP) -O binary $(OBJCOPY_OPT)  
