ifneq ($(TRNG_MK_INC),Y)
    TRNG_MK_INC=Y

    TRNG_DIR = $(MCAL_COMMON_DIR)/trng
    # $(error TRNG_DIR=$(TRNG_DIR))

    INCDIR += -I$(TRNG_DIR)

    MCAL_OPT += -DHAS_TRNG

    ifeq ($(TRNG_PROC),Y)
        MCAL_OPT += -DHAS_TRNG_PROC
    endif

    SOURCES_C += $(TRNG_DIR)/trng_general.c

    ifeq ($(TRNG_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_TRNG_INTERRUPTS
        SOURCES_C += $(TRNG_DIR)/trng_isr.c
    endif

    # must be outside
    SOURCES_C += $(TRNG_DIR)/trng_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(TRNG_DIAG),Y)
            MCAL_OPT += -DHAS_TRNG_DIAG
            SOURCES_DIAG_C += $(TRNG_DIR)/trng_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TRNG_COMMANDS),Y)
            MCAL_OPT += -DHAS_TRNG_COMMANDS
            SOURCES_C += $(TRNG_DIR)/trng_commands.c
        endif
    endif
endif
