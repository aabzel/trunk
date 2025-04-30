ifneq ($(I2C_NRF_MK_INC),Y)
    I2C_NRF_MK_INC=Y

    I2C_NRF_DIR = $(MCAL_NRF5340_DIR)/i2c
    #@echo $(error I2C_NRF_DIR=$(I2C_NRF_DIR))

    INCDIR += -I$(I2C_NRF_DIR)
    OPT += -DHAS_I2C

    SOURCES_C += $(I2C_NRF_DIR)/i2c_drv.c
    SOURCES_C += $(I2C_NRF_DIR)/i2c_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            OPT += -DHAS_I2C_DIAG
            SOURCES_C += $(I2C_NRF_DIR)/i2c_nrf_diag.c
        endif
    endif

    ifeq ($(I2C0),Y)
        OPT += -DHAS_I2C0
    endif

    ifeq ($(I2C1),Y)
        OPT += -DHAS_I2C1
    endif

    ifeq ($(I2C2),Y)
        OPT += -DHAS_I2C2
    endif

    ifeq ($(I2C3),Y)
        OPT += -DHAS_I2C3
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            OPT += -DHAS_I2C_COMMANDS
            SOURCES_C += $(I2C_NRF_DIR)/i2c_nrf_commands.c
        endif
    endif
endif