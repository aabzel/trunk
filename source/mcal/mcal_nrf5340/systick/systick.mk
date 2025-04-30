$(info SYSTICK_NRF53_MK_INC=$(SYSTICK_NRF53_MK_INC) )
ifneq ($(SYSTICK_NRF53_MK_INC),Y)
    SYSTICK_NRF53_MK_INC=Y

    NRF53_SYSTICK_DIR = $(MCAL_NRF5340_DIR)/systick
    #@echo $(error SYSTICK_DIR=$(SYSTICK_DIR))
    INCDIR += -I$(NRF53_SYSTICK_DIR)
    OPT += -DHAS_CUSTOM_SYSTICK
    OPT += -DHAS_SYSTICK_CUSTOM
    OPT += -DHAS_SYSTICK_INT

    SOURCES_C += $(NRF53_SYSTICK_DIR)/systick_custom.c

    ifeq ($(SYSTICK_DIAG),Y)
        SOURCES_C += $(NRF53_SYSTICK_DIR)/systick_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SYSTICK_COMMANDS),Y)
            OPT += -DHAS_SYSTICK_CUSTOM_COMMANDS
            SOURCES_C += $(NRF53_SYSTICK_DIR)/systick_custom_commands.c
        endif
    endif
endif
