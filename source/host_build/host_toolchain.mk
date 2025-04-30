
PREFIX=

$(info WithOutPath)
PREPROCESSOR_TOOL = $(PREFIX)cpp.exe
CC =$(PREFIX)gcc.exe
CPP =$(PREFIX)g++.exe
AS =$(PREFIX)gcc -x assembler-with-cpp
CP =$(PREFIX)objcopy.exe
SZ =$(PREFIX)size.exe

# the compiler to use
ifeq ($(MINGW),Y)
    COMPILE_OPT += -DHAS_GCC
    CC=C:\MinGW\bin\gcc.exe
endif

ifeq ($(CLANG),Y)
    COMPILE_OPT += -DHAS_CLANG
    #CC=C:\cygwin64\bin\clang
    CC ="C:\Program Files\LLVM\bin\clang.exe"
endif

ifeq ($(CYGWIN64),Y)
    COMPILE_OPT += -DHAS_GCC
    CC=C:\cygwin64\bin\gcc.exe
endif

ifeq ($(TCC),Y)
    COMPILE_OPT += -DHAS_TCC
    CC=tcc.exe
endif


#@echo $(error CC= $(CC))

