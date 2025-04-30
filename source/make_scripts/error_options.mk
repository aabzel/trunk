#OPT_C += -Werror=cast-align
#OPT_C += -Werror=conversion
#OPT_C += -Werror=duplicate-decl-specifier
#OPT_C += -Werror=duplicated-branches # usefull
#OPT_C += -Werror=enum-conversion
#OPT_C += -Werror=sign-compare
#OPT_C += -Werror=sign-conversion
#OPT_C += -Werror=string-compare
OPT_C += -Werror=address
OPT_C += -Werror=array-bounds=1
OPT_C += -Werror=comment
OPT_C += -Werror=duplicated-cond
OPT_C += -Werror=empty-body
OPT_C += -Werror=enum-compare
OPT_C += -Werror=float-equal
OPT_C += -Werror=logical-op
OPT_C += -Werror=incompatible-pointer-types
OPT_C += -Werror=maybe-uninitialized
OPT_C += -Werror=misleading-indentation
OPT_C += -Werror=missing-field-initializers
OPT_C += -Werror=missing-parameter-type
OPT_C += -Werror=old-style-declaration
OPT_C += -Werror=overflow
OPT_C += -Werror=override-init
OPT_C += -Werror=pointer-sign
OPT_C += -Werror=duplicate-decl-specifier
OPT_C += -Werror=return-type
OPT_C += -Werror=shift-count-overflow
OPT_C += -Werror=shift-negative-value
OPT_C += -Werror=switch
OPT_C += -Werror=type-limits
OPT_C += -Werror=missing-braces
OPT_C += -Werror=uninitialized
OPT_C += -Werror=unused-but-set-parameter
OPT_C += -Werror=unused-but-set-variable
OPT_C += -Werror=unused-function
OPT_C += -Werror=unused-value
OPT_C += -Werror=unused-variable
OPT_C += -Werror=int-conversion # StrDup
#OPT_C += -Werror=redundant-decls # freeRTOSErr
OPT_C += -Werror=implicit-function-declaration

CFLAGS += -Wall

ifneq ($(EHAL),Y)
   ifneq ($(EHAL_MCAL),Y)
        OPT_C += -Werror=unused-but-set-variable
        #OPT_C += -Werror=implicit-function-declaration
        OPT_C += -Werror=unused-variable
    endif
endif


