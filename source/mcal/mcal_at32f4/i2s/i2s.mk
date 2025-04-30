$(info I2S_MK_INC=$(I2S_MK_INC))

ifneq ($(I2S_MK_INC),Y)
    I2S_MK_INC=Y

    I2S_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/i2s
    #@echo $(error I2S_CUSTOM_DIR=$(I2S_CUSTOM_DIR))

    INCDIR += -I$(I2S_CUSTOM_DIR)
    OPT += -DHAS_I2S
    OPT += -DHAS_SPI_PROC

    ifeq ($(I2S1),Y)
        OPT += -DHAS_I2S1
    endif

    ifeq ($(I2S2),Y)
        OPT += -DHAS_I2S2

        ifeq ($(I2S2_RX),Y)
            OPT += -DHAS_I2S2_RX
        endif

        ifeq ($(I2S2_TX),Y)
            OPT += -DHAS_I2S2_TX
        endif
    endif

    ifeq ($(I2S3),Y)
        OPT += -DHAS_I2S3
    endif

    ifeq ($(I2S4),Y)
        OPT += -DHAS_I2S4
    endif

    ifeq ($(I2S5),Y)
        OPT += -DHAS_I2S5
    endif

    ifeq ($(I2S6),Y)
        OPT += -DHAS_I2S6
    endif
    
    ifeq ($(I2S_ISR),Y)
        OPT += -DHAS_I2S_ISR
        SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_custom_isr.c
    endif

    SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_mcal.c

    ifeq ($(I2S_DMA),Y)
        OPT += -DHAS_I2S_DMA
        SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_dma_mcal.c
    endif

    ifeq ($(DIAG),Y)
            ifeq ($(I2S_DIAG),Y)
            OPT += -DHAS_I2S_CUSTOM_DIAG
            SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2S_COMMANDS),Y)
            OPT += -DHAS_I2S_CUSTOM_COMMANDS
            SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_custom_commands.c
        endif
    endif
endif
