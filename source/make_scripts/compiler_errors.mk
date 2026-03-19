# COMPILE_GCC_OPT += -Werror=pedantic
 
# $(error WORKSPACE_LOC=$(WORKSPACE_LOC))

COMPILE_GCC_OPT += -Werror=all

#This enables some extra warning flags that are not enabled by вЂ�-WallвЂ™.
COMPILE_GCC_OPT += -Werror=extra

#Warn for variables that might be changed by longjmp or vfork. T
COMPILE_GCC_OPT += -Werror=clobbered

#Warn if an empty body occurs in an if, else or do while statement.
COMPILE_GCC_OPT += -Werror=empty-body

#Warn if a structureвЂ™s initializer has some fields missing.
COMPILE_GCC_OPT += -Werror=missing-parameter-type

#Warn when a switch case falls through.
#COMPILE_GCC_OPT += -Wimplicit-fallthrough=5
#COMPILE_GCC_OPT += -Werror=implicit-fallthrough (cc1.exe: error: -Werror=implicit-fallthrough: no option -Wimplicit-fallthrough)

#Warn if a structureвЂ™s initializer has some fields missing.
COMPILE_GCC_OPT += -Werror=missing-field-initializers

#Warn for obsolescent usages, according to the C Standard, in a declaration. For
#example, warn if storage-class specifiers like static are not the first things in
#a declaration. 
COMPILE_GCC_OPT += -Werror=old-style-declaration

#Warn if an initialized field without side effects is overridden when 
#using designated initializers
COMPILE_GCC_OPT += -Werror=override-init

COMPILE_GCC_OPT += -Werror=strict-overflow=1

#Warn for calls to strcmp and strncmp whose result is determined to be either
#zero or non-zero in tests for such equality owing to the length of one argument
#being greater than the size of the array the other argument is stored in (or the
#bound in the case of strncmp). Such calls could be mistakes. 
  #COMPILE_GCC_OPT += -Werror=string-compare
  # (-Werror=string-compare cause strange build errors)

#Warn if a comparison is always true or always false due to the limited range of
#the data type, but do not warn for constant expressions. For example, warn if
#an unsigned variable is compared against zero with < or >=. 
COMPILE_GCC_OPT += -Werror=type-limits

#Warn if an automatic variable is used without first being initialized.
COMPILE_GCC_OPT += -Werror=uninitialized

#Warn whenever a function parameter is assigned to, but otherwise unused (aside
#from its declaration).
COMPILE_GCC_OPT += -Werror=unused-but-set-parameter


# warnings from casts from a pointer to an integer type of a different size.
COMPILE_GCC_OPT += -Werror=pointer-to-int-cast

# warnings from casts to pointer type of an integer of a different size.
COMPILE_GCC_OPT += -Werror=int-to-pointer-cast

ifneq ($(FAT_FS),Y)
    #Warn whenever a switch statement does not have a default case.
    COMPILE_GCC_OPT += -Werror=switch-default
endif


# Warn whenever a switch statement has an index of enumerated type and lacks
# a case for one or more of the named codes of that enumeration. case labels
# outside the enumeration range also provoke warnings when this option is used.
# The only difference between вЂ�-WswitchвЂ™ and this option is that this option gives
# a warning about an omitted enumeration code even if there is a default label
   # COMPILE_GCC_OPT += -Werror=switch-enum
   # (switch-enum) useless due to XXX_UNDEF const in each enumeration


COMPILE_GCC_OPT += -Werror=init-self
COMPILE_GCC_OPT += -Werror=logical-not-parentheses
COMPILE_GCC_OPT += -Werror=memset-transposed-args
COMPILE_GCC_OPT += -Werror=misleading-indentation
COMPILE_GCC_OPT += -Werror=parentheses
COMPILE_GCC_OPT += -Werror=return-type
COMPILE_GCC_OPT += -Werror=sign-compare
COMPILE_GCC_OPT += -Werror=sequence-point
COMPILE_GCC_OPT += -Werror=uninitialized
COMPILE_GCC_OPT += -Werror=unused-function
COMPILE_GCC_OPT += -Werror=unused-variable
COMPILE_GCC_OPT += -Werror=sizeof-pointer-memaccess
COMPILE_GCC_OPT += -Werror=strict-aliasing
COMPILE_GCC_OPT += -Werror=switch
COMPILE_GCC_OPT += -Werror=tautological-compare
COMPILE_GCC_OPT += -Werror=trigraphs



COMPILE_GCC_OPT += -Werror=array-bounds=1
COMPILE_GCC_OPT += -Werror=address
COMPILE_GCC_OPT += -Werror=bool-compare
COMPILE_GCC_OPT += -Werror=char-subscripts
COMPILE_GCC_OPT += -Werror=comment
COMPILE_GCC_OPT += -Werror=duplicated-cond
COMPILE_GCC_OPT += -Werror=enum-compare
COMPILE_GCC_OPT += -Werror=logical-op
COMPILE_GCC_OPT += -Werror=return-local-addr
COMPILE_GCC_OPT += -Werror=implicit-function-declaration
COMPILE_GCC_OPT += -Werror=div-by-zero
COMPILE_GCC_OPT += -Werror=duplicated-cond
COMPILE_GCC_OPT += -Werror=enum-compare
COMPILE_GCC_OPT += -Werror=empty-body
COMPILE_GCC_OPT += -Werror=unused-but-set-variable
COMPILE_GCC_OPT += -Werror=logical-op
COMPILE_GCC_OPT += -Werror=implicit-int
COMPILE_GCC_OPT += -Werror=incompatible-pointer-types
COMPILE_GCC_OPT += -Werror=maybe-uninitialized
COMPILE_GCC_OPT += -Werror=missing-parameter-type
COMPILE_GCC_OPT += -Werror=overflow
COMPILE_GCC_OPT += -Werror=pointer-sign
COMPILE_GCC_OPT += -Werror=shift-count-overflow
COMPILE_GCC_OPT += -Werror=unused-but-set-variable
COMPILE_GCC_OPT += -Werror=incompatible-pointer-types
COMPILE_GCC_OPT += -Werror=missing-parameter-type
COMPILE_GCC_OPT += -Werror=old-style-declaration
COMPILE_GCC_OPT += -Werror=pointer-sign
COMPILE_GCC_OPT += -Werror=shift-count-overflow
COMPILE_GCC_OPT += -Werror=shift-negative-value
COMPILE_GCC_OPT += -Werror=missing-braces
COMPILE_GCC_OPT += -Werror=unused-but-set-variable
COMPILE_GCC_OPT += -Werror=unused-function
COMPILE_GCC_OPT += -Werror=unused-value
COMPILE_GCC_OPT += -Werror=pointer-arith
COMPILE_GCC_OPT += -Werror=unused-but-set-variable
COMPILE_GCC_OPT += -Werror=int-conversion # StrDup
#COMPILE_GCC_OPT += -Werror=redundant-decls # freeRTOSErr
COMPILE_GCC_OPT += -Werror=implicit-function-declaration

   
ifneq ($(EHAL),Y)
   ifneq ($(EHAL_MCAL),Y)
        COMPILE_GCC_OPT += -Werror=unused-but-set-variable
        #COMPILE_GCC_OPT += -Werror=implicit-function-declaration
        COMPILE_GCC_OPT += -Werror=unused-variable
    endif
endif


ifneq ($(MINGW),Y)
    # (not supported in MINGW)
    # COMPILE_GCC_OPT += -Werror=uninitialised
    # COMPILE_GCC_OPT += -Werror=enum-int-mismatch
    COMPILE_GCC_OPT += -Werror=strict-prototypes
    COMPILE_GCC_OPT += -Werror=duplicate-decl-specifier
    COMPILE_GCC_OPT += -Werror=address-of-packed-member
    COMPILE_GCC_OPT += -Werror=sizeof-pointer-div 
    COMPILE_GCC_OPT += -Werror=int-in-bool-context 
    COMPILE_GCC_OPT += -Werror=bool-operation 
    COMPILE_GCC_OPT += -Werror=memset-elt-size 
    COMPILE_GCC_OPT += -Werror=multistatement-macros 

    #(ignored-qualifiers)Warn if the return type of a function has a type qualifier such as const. For
    #ISO C such a type qualifier has no effect, since the value returned by a function
    #is not an lvalue. For C++, the warning is only emitted for scalar types or void.
    #ISO C prohibits qualified void return types on function definitions, so such
    #return types always receive a warning even without this option.
    COMPILE_GCC_OPT += -Werror=ignored-qualifiers
endif

ifneq ($(XPRINTF),Y)
    #Warn if floating-point values are used in equality comparisons.
    COMPILE_GCC_OPT += -Werror=float-equal
endif

ifeq ($(EXTRA_VERIFICATION),Y)
    COMPILE_GCC_OPT += -Werror=missing-declarations
    COMPILE_GCC_OPT += -Werror=missing-prototypes
    COMPILE_GCC_OPT += -Werror=unused-variable
endif

ifeq ($(EXTRA_VERIFICATION2),Y)
    # Warn for implicit conversions that may alter a value. This includes conversions
    # between real and integer, like abs (x) when x is double; conversions between
    COMPILE_GCC_OPT += -Werror=conversion

    #Warn if anything is declared more than once in the same scope, even in cases
    #where multiple declaration is valid and changes nothing.
    COMPILE_GCC_OPT += -Werror=redundant-decls
    
    COMPILE_GCC_OPT += -Werror=float-conversion

    # Warn about incompatible integer to pointer and pointer to integer conversions.
    # This warning is about implicit conversions; for explicit conversions
    # the warnings вЂ�-Wno-int-to-pointer-castвЂ™ and вЂ�-Wno-pointer-to-int-castвЂ™
    # may be used.
    COMPILE_GCC_OPT += -Werror=int-conversion

    # Warn whenever a local variable or type declaration shadows another
    # variable, parameter, type, class member (in C++), or instance variable (in
    # Objective-C) or whenever a built-in function is shadowed. Note that in C++,
    # the compiler warns if a local variable shadows an explicit typedef, but not if
    # it shadows a struct/class/enum. If this warning is enabled, it includes also
    # all instances of local shadowing. This means that вЂ�-Wno-shadow=localвЂ™ and
    # вЂ�-Wno-shadow=compatible-localвЂ™ are ignored when вЂ�-WshadowвЂ™ is used. Same
    # as вЂ�-Wshadow=globalвЂ™.
    COMPILE_GCC_OPT += -Werror=shadow
    
    # Check calls to printf and scanf, etc., to make sure that the arguments supplied
    # have types appropriate to the format string specified, and that the conversions
    # specified in the format string make sense.
    COMPILE_GCC_OPT += -Werror=format
endif

ifeq ($(EXTRA_VERIFICATION3),Y)
    COMPILE_GCC_OPT += -Werror=float-conversion
    
    # Warn if padding is included in a structure, either to align an element of the
    # structure or to align the whole structure. 
    # Sometimes when this happens it is possible to rearrange the fields of the structure to 
    # reduce the padding and so make the structure smaller.
    COMPILE_GCC_OPT += -Werror=padded

endif


#COMPILE_GCC_OPT += -Werror=cast-align
#COMPILE_GCC_OPT += -Werror=duplicate-decl-specifier
#COMPILE_GCC_OPT += -Werror=duplicated-branches # usefull
#COMPILE_GCC_OPT += -Werror=enum-conversion
#COMPILE_GCC_OPT += -Werror=sign-conversion



#COMPILE_GCC_OPT += -Werror=discarded-qualifiers
#COMPILE_GCC_OPT += -Werror=type-limits
#COMPILE_GCC_OPT += -Werror=override-init
#COMPILE_GCC_OPT += -Werror=duplicate-decl-specifier
#COMPILE_GCC_OPT += -Werror=traditional

COMPILE_GCC_OPT += -Werror=unused

ifeq ($(C_XX),Y)
    COMPILE_GCC_OPT += -Werror=reorder
    COMPILE_GCC_OPT += -Werror=redundant-move
    COMPILE_GCC_OPT += -Werror=pessimizing-move 
endif