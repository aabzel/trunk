

COMPILE_GCC_OPT += -Wextra

#COMPILE_GCC_OPT += -Wpedantic
#COMPILE_GCC_OPT += -Wsign-compare

#COMPILE_GCC_OPT += -Werror=int-conversion
ifeq ($(EXTRA_VERIFICATION),Y)
    COMPILE_OPT += -Wconversion
endif


COMPILE_GCC_OPT += -Wno-sign-compare
COMPILE_GCC_OPT += -Wno-unused-parameter
COMPILE_GCC_OPT += -Wno-implicit-fallthrough
COMPILE_GCC_OPT += -Wno-stringop-truncation
COMPILE_GCC_OPT += -Wno-format-truncation
COMPILE_GCC_OPT += -Wno-restrict
COMPILE_GCC_OPT += -Wno-format
COMPILE_GCC_OPT += -Wno-cpp #TODO temp
COMPILE_GCC_OPT += -Wno-discarded-qualifiers