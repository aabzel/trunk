$(info PIN_GENERAL_DRV_MK_INC=$(PIN_GENERAL_DRV_MK_INC) )
ifneq ($(PIN_GENERAL_DRV_MK_INC),Y)
    PIN_GENERAL_DRV_MK_INC=Y

    PIN_MCAL_DIR = $(MCAL_COMMON_DIR)/pin
    # $(error PIN_MCAL_DIR=$(PIN_MCAL_DIR))

    INCDIR += -I$(PIN_MCAL_DIR)
    MCAL_OPT += -DHAS_PIN
 
    ifeq ($(PIN_PROC),Y)
        MCAL_OPT += -DHAS_PIN_PROC
    endif

    ifeq ($(PIN_EXT),Y)
        MCAL_OPT += -DHAS_PIN_EXT
    endif

    ifeq ($(PINS),Y)
        MCAL_OPT += -DHAS_PINS
        MCAL_OPT += -DHAS_PIN
    endif
    
    SOURCES_C += $(PIN_MCAL_DIR)/pin_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(PIN_DIAG),Y)
            MCAL_OPT += -DHAS_PIN_DIAG
            SOURCES_C += $(PIN_MCAL_DIR)/pin_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PIN_COMMANDS),Y)
            MCAL_OPT += -DHAS_PIN_COMMANDS
            SOURCES_C += $(PIN_MCAL_DIR)/pin_commands.c
        endif
    endif
    
endif