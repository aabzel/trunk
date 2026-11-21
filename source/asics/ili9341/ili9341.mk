ifneq ($(ILI9341_MK_INC),Y)
    ILI9341_MK_INC=Y

    ILI9341_DIR = $(ASICS_DIR)/ili9341
    # $(error ILI9341_DIR=$(ILI9341_DIR))

    INCDIR += -I$(ILI9341_DIR)

    MCAL_OPT += -DHAS_ILI9341

    ifeq ($(ILI9341_PROC),Y)
        MCAL_OPT += -DHAS_ILI9341_PROC
    endif

    ifeq ($(ILI9341_FRAME_BUFFER),Y)
        MCAL_OPT += -DHAS_ILI9341_FRAME_BUFFER
    endif

    SOURCES_C += $(ILI9341_DIR)/ili9341_mcal.c

    ifeq ($(ILI9341_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_ILI9341_INTERRUPTS
        SOURCES_C += $(ILI9341_DIR)/ili9341_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(ILI9341_DIAG),Y)
            MCAL_OPT += -DHAS_ILI9341_DIAG
            SOURCES_DIAG_C += $(ILI9341_DIR)/ili9341_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ILI9341_COMMANDS),Y)
            MCAL_OPT += -DHAS_ILI9341_COMMANDS
            SOURCES_C += $(ILI9341_DIR)/ili9341_commands.c
        endif
    endif
endif
