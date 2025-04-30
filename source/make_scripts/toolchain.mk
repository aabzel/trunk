
PYTHON_BIN=python.exe

ifeq ($(ARM), Y)
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

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
