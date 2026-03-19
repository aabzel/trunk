
# Warnings that need to be muted

#n when comparing an argument marked with the nonnull function attribute against null inside the function.
COMPILE_GCC_OPT += -Wno-nonnull-compare
COMPILE_GCC_OPT += -Wno-stringop-truncation
COMPILE_GCC_OPT += -Wno-format-truncation
COMPILE_GCC_OPT += -Wno-restrict
COMPILE_GCC_OPT += -Wno-format

COMPILE_GCC_OPT += -Wno-redundant-decls

ifeq ($(INDULGENCE_LEVEL_1), Y)
    # Cam code is too weak and unable to builds with that
    COMPILE_GCC_OPT += -Wno-ignored-qualifiers
endif

ifeq ($(INDULGENCE_LEVEL_2), Y)
    # Unit tests has too many skips for severe skip of init
    COMPILE_GCC_OPT += -Wno-missing-field-initializers
endif

# Do not warn if type qualifiers on pointers are being discarded. Typically, the
# compiler warns if a const char * variable is passed to a function that takes a
# char * parameter. This option can be used to suppress such a warning.
COMPILE_GCC_OPT += -Wno-discarded-qualifiers


# Not warn about incompatible integer to pointer and pointer to integer 
# conversions. This
COMPILE_GCC_OPT += -Wno-int-conversion

# Warn whenever a switch statement has an index of boolean type and the case
# values are outside the range of a boolean type.
COMPILE_GCC_OPT += -Wno-switch-bool

COMPILE_GCC_OPT += -Wno-conversion #TODO temp
COMPILE_GCC_OPT += -Wno-cpp #TODO temp

COMPILE_GCC_OPT += -Wno-sign-compare
COMPILE_GCC_OPT += -Wno-unused-parameter
COMPILE_GCC_OPT += -Wno-implicit-fallthrough
COMPILE_GCC_OPT += -Wno-restrict

# Make all warnings into errors.
COMPILE_GCC_OPT += -Werror 