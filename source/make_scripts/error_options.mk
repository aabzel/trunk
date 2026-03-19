#COMPILE_GCC_OPT += -Werror=cast-align
#COMPILE_GCC_OPT += -Werror=conversion
#COMPILE_GCC_OPT += -Werror=duplicate-decl-specifier
#COMPILE_GCC_OPT += -Werror=duplicated-branches # usefull
#COMPILE_GCC_OPT += -Werror=enum-conversion
#COMPILE_GCC_OPT += -Werror=sign-compare
#COMPILE_GCC_OPT += -Werror=sign-conversion
#COMPILE_GCC_OPT += -Werror=string-compare
COMPILE_GCC_OPT += -Werror=address
COMPILE_GCC_OPT += -Werror=array-bounds=1
COMPILE_GCC_OPT += -Werror=comment
COMPILE_GCC_OPT += -Werror=duplicated-cond
COMPILE_GCC_OPT += -Werror=empty-body
COMPILE_GCC_OPT += -Werror=enum-compare
COMPILE_GCC_OPT += -Werror=float-equal
COMPILE_GCC_OPT += -Werror=logical-op
COMPILE_GCC_OPT += -Werror=incompatible-pointer-types
COMPILE_GCC_OPT += -Werror=maybe-uninitialized
COMPILE_GCC_OPT += -Werror=misleading-indentation
COMPILE_GCC_OPT += -Werror=missing-field-initializers
COMPILE_GCC_OPT += -Werror=missing-parameter-type
COMPILE_GCC_OPT += -Werror=old-style-declaration
COMPILE_GCC_OPT += -Werror=overflow
COMPILE_GCC_OPT += -Werror=override-init
COMPILE_GCC_OPT += -Werror=pointer-sign
COMPILE_GCC_OPT += -Werror=duplicate-decl-specifier
COMPILE_GCC_OPT += -Werror=return-type
COMPILE_GCC_OPT += -Werror=shift-count-overflow
COMPILE_GCC_OPT += -Werror=shift-negative-value
COMPILE_GCC_OPT += -Werror=switch
COMPILE_GCC_OPT += -Werror=type-limits
COMPILE_GCC_OPT += -Werror=missing-braces
COMPILE_GCC_OPT += -Werror=uninitialized
COMPILE_GCC_OPT += -Werror=unused-but-set-parameter
COMPILE_GCC_OPT += -Werror=unused-but-set-variable
COMPILE_GCC_OPT += -Werror=unused-function
COMPILE_GCC_OPT += -Werror=unused-value
COMPILE_GCC_OPT += -Werror=unused-variable
COMPILE_GCC_OPT += -Werror=int-conversion # StrDup
#COMPILE_GCC_OPT += -Werror=redundant-decls # freeRTOSErr
COMPILE_GCC_OPT += -Werror=implicit-function-declaration

CFLAGS += -Wall

ifneq ($(EHAL),Y)
   ifneq ($(EHAL_MCAL),Y)
        COMPILE_GCC_OPT += -Werror=unused-but-set-variable
        #COMPILE_GCC_OPT += -Werror=implicit-function-declaration
        COMPILE_GCC_OPT += -Werror=unused-variable
    endif
endif


