$(info I2S_CUSTOM_MK_INC=$(I2S_CUSTOM_MK_INC))

ifneq ($(I2S_CUSTOM_MK_INC),Y)
    I2S_CUSTOM_MK_INC=Y

    I2S_CUSTOM_DIR = $(MCAL_CUSTOM_DIR)/i2s
    # $(error I2S_CUSTOM_DIR=$(I2S_CUSTOM_DIR))

    INCDIR += -I$(I2S_CUSTOM_DIR)
    MCAL_OPT += -DHAS_I2S_CUSTOM
    MCAL_OPT += -DHAS_I2S_ISR

    SOURCES_DIAG_C += $(I2S_CUSTOM_DIR)/i2s_custom_misc.c
    SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_mcal.c
    
    SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_callbacks.c

    ifeq ($(I2S_GPIO),Y)
        MCAL_OPT += -DHAS_I2S_GPIO
    endif

    ifeq ($(I2S_FULL_DUPLEX),Y)
        MCAL_OPT += -DSPI_I2S_FULLDUPLEX_SUPPORT
        MCAL_OPT += -DHAS_I2S_FULL_DUPLEX
        SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_full_duplex.c
    endif

    ifeq ($(I2S_DMA),Y)
        MCAL_OPT += -DHAS_I2S_DMA
        SOURCES_C += $(I2S_CUSTOM_DIR)/dma_channel_config_i2s.c
        SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_dma_custom.c
    endif

    ifeq ($(I2S1),Y)
        $(info Add I2S1)
        SOURCES_C += $(I2S_CUSTOM_DIR)/dma_channel_config_i2s1.c
        MCAL_OPT += -DHAS_I2S1
    endif

    ifeq ($(I2S2),Y)
        $(info Add I2S2)
        SOURCES_C += $(I2S_CUSTOM_DIR)/dma_channel_config_i2s2.c
        MCAL_OPT += -DHAS_I2S2
    endif
    
    ifeq ($(I2S3),Y)
        $(info Add I2S3)
        SOURCES_C += $(I2S_CUSTOM_DIR)/dma_channel_config_i2s3.c
        MCAL_OPT += -DHAS_I2S3
    endif

    ifeq ($(I2S4),Y)
        $(info Add I2S4)
        SOURCES_C += $(I2S_CUSTOM_DIR)/dma_channel_config_i2s4.c
        MCAL_OPT += -DHAS_I2S4
    endif

    ifeq ($(I2S5),Y)
        SOURCES_C += $(I2S_CUSTOM_DIR)/dma_channel_config_i2s5.c
        MCAL_OPT += -DHAS_I2S5
    endif

    ifeq ($(DIAG),Y)
        MCAL_OPT += -DHAS_I2S_CUSTOM_DIAG
        SOURCES_DIAG_C += $(I2S_CUSTOM_DIR)/i2s_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2S_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2S_CUSTOM_COMMANDS
            SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_custom_commands.c
        endif
    endif
endif
