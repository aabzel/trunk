$(info I2S_MCAL_MK_INC=  $(I2S_MCAL_MK_INC) )

ifneq ($(I2S_MCAL_MK_INC),Y)
    I2S_MCAL_MK_INC=Y

    #I2S_VOLUME=Y
    I2S_MCAL_DIR = $(MCAL_COMMON_DIR)/i2s
    # $(error I2S_MCAL_DIR=$(I2S_MCAL_DIR))

    INCDIR += -I$(I2S_MCAL_DIR)
    MCAL_OPT += -DHAS_I2S
    
    I2S_ISR=Y
    
    ifeq ($(I2S_PROC),Y)
        MCAL_OPT += -DHAS_I2S_PROC
    endif

    ifeq ($(I2S_FULL_DUPLEX),Y)
        MCAL_OPT += -DHAS_I2S_FULL_DUPLEX
    endif

    ifeq ($(I2S_DMA),Y)
        MCAL_OPT += -DHAS_I2S_DMA
        SOURCES_C += $(I2S_MCAL_DIR)/i2s_dma_mcal.c
    endif
    
    ifeq ($(I2S_ISR),Y)
        MCAL_OPT += -DHAS_I2S_ISR
        SOURCES_C += $(I2S_MCAL_DIR)/i2s_isr.c
    endif

    ifeq ($(I2S_RX),Y)
        MCAL_OPT += -DHAS_I2S_RX
    endif
        
    ifeq ($(I2S_VOLUME),Y)
        MCAL_OPT += -DHAS_I2S_VOLUME
        SOURCES_C += $(I2S_MCAL_DIR)/i2s_volume.c
    endif

    SOURCES_C += $(I2S_MCAL_DIR)/i2s_general.c
    

    ifeq ($(DIAG),Y)
        ifeq ($(I2S_DIAG),Y)
            MCAL_OPT += -DHAS_I2S_DIAG
            SOURCES_DIAG_C += $(I2S_MCAL_DIR)/i2s_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(I2S_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2S_COMMANDS
            SOURCES_C += $(I2S_MCAL_DIR)/i2s_commands.c
        endif
    endif
endif