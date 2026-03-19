

#COMPILE_GCC_OPT += -fopt-info


#see https://habr.com/ru/articles/425071/
#COMPILE_GCC_OPT += -finstrument-functions

#Make all warnings into errors.
#COMPILE_GCC_OPT += -Werror

 # (-Wall) This enables all the warnings about constructions that some users consider
# questionable, and that are easy to avoid (or modify to prevent the warning),
# even in conjunction with macros.
COMPILE_GCC_OPT += -Wall


 
#-ffunction-sections Place each function or data item into its own section in the output file if the
#target supports arbitrary sections. The name of the function or the name of
#the data item determines the sectionвЂ™s name in the output file.
COMPILE_GCC_OPT += -ffunction-sections



#Place each function or data item into its own section in the output file if the
#target supports arbitrary sections. The name of the function or the name of
#the data item determines the sectionвЂ™s name in the output file.
COMPILE_GCC_OPT += -fdata-sections


COMPILE_GCC_OPT += -fshort-enums


COMPILE_GCC_OPT += -fomit-frame-pointer


COMPILE_GCC_OPT += -fno-move-loop-invariants


#Perform dead code elimination
COMPILE_GCC_OPT += -fdce

#Perform dead store elimination
COMPILE_GCC_OPT += -fdse

COMPILE_GCC_OPT += -fmax-errors=70
COMPILE_GCC_OPT += -fmessage-length=0
COMPILE_GCC_OPT += -fsigned-char
COMPILE_GCC_OPT += -fno-common
COMPILE_GCC_OPT += -fstack-usage
COMPILE_GCC_OPT += -fzero-initialized-in-bss
COMPILE_GCC_OPT += -finline-small-functions
COMPILE_GCC_OPT += -finline-functions







ifeq ($(DEBUG), Y)
    # $(error DEBUG=$(DEBUG))

    # Reduce compilation time and make debugging produce the expected results.
    OPTIMIZATION = -O0

    # Request debugging information and also use level to specify how much information.
    # -g3 Level 3 includes extra information, such as all the macro definitions present in
    # the program. 
    # Some debuggers support macro expansion when you use -g3.
    COMPILE_GCC_OPT += -g3 

    # Produce debugging information for use by GDB. This means to use the most
    # expressive format available (DWARF, stabs, or the native format if neither of
    # those are supported), including GDB extensions if at all possible.
    #COMPILE_GCC_OPT += -ggdb 
    
    #Produce debugging information in DWARF format (if that is supported). 
    #COMPILE_GCC_OPT += -gdwarf-2
else
    # Optimize for size. пїЅ-OsпїЅ enables all пїЅ-O2пїЅ optimizations except those that often
    # increase code size: -falign-functions  -falign-jumps -falign-labels  -falign-loops
    # -fprefetch-loop-arrays  -freorder-blocks-algorithm=stc It also enables пїЅ-finline-functionsпїЅ
    # , causes the compiler to tune for code size rather than execution speed, and 
    # performs further optimizations designed to reduce code size.
    OPTIMIZATION = -Os
endif

ifeq ($(HI_PERF), Y)
# Disregard strict standards compliance. вЂ�-OfastвЂ™ enables all вЂ�-O3вЂ™ optimizations. 
# It also enables optimizations that are not valid for all standard-compliant programs. 
# It turns on вЂ�-ffast-mathвЂ™, вЂ�-fallow-store-data-racesвЂ™ and the Fortran-specific 
# вЂ�-fstack-arraysвЂ™, unless вЂ�-fmax-stack-var-sizeвЂ™ is specified, and вЂ�-fno-protect-parensвЂ™.
    OPTIMIZATION = -Ofast
endif

ifeq ($(PACK_PROGRAM), Y)
     $(error PACK_PROGRAM=$(PACK_PROGRAM))
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
