$(info TRNG_DRV_MK_INC=  $(TRNG_DRV_MK_INC) )
ifneq ($(TRNG_DRV_MK_INC),Y)
    TRNG_DRV_MK_INC=Y

    TRNG_CUSTOM_DIR = $(MCAL_X86_DIR)/trng
    # $(error TRNG_CUSTOM_DIR=$(TRNG_CUSTOM_DIR))

    INCDIR += -I$(TRNG_CUSTOM_DIR)
    MCAL_OPT += -DHAS_TRNG_CUSTOM

    ifeq ($(TRNG_PROC),Y)
        MCAL_OPT += -DHAS_TRNG_PROC
    endif

    SOURCES_C += $(TRNG_CUSTOM_DIR)/trng_mcal.c

    ifeq ($(CLI),Y)
        ifeq ($(TRNG_DIAG),Y)
            MCAL_OPT += -DHAS_TRNG_CUSTOM_DIAG
            SOURCES_C += $(TRNG_CUSTOM_DIR)/trng_custom_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(TRNG_COMMANDS),Y)
            MCAL_OPT += -DHAS_TRNG_CUSTOM_COMMANDS
            SOURCES_C += $(TRNG_CUSTOM_DIR)/trng_custom_commands.c
        endif
    endif
endif