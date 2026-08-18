ifneq ($(SI4703_MK_INC),Y)
    SI4703_MK_INC=Y

    SI4703_DIR = $(ASICS_DIR)/si4703
    # $(error SI4703_DIR=$(SI4703_DIR))

    INCDIR += -I$(SI4703_DIR)

    MCAL_OPT += -DHAS_SI4703
    MCAL_OPT += -DBUS_MOD_SEL_METHOD1
    MCAL_OPT += -DHAS_SI4703_PROC
    MCAL_OPT += -DHAS_FM_TUNER
    SOURCES_C += $(SI4703_DIR)/si4703_mcal.c

    ifeq ($(RDS),Y)
        MCAL_OPT += -DHAS_RDS
        SOURCES_C += $(SI4703_DIR)/si4703_rds_drv.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SI4703_DIAG),Y)
            MCAL_OPT += -DHAS_SI4703_DIAG
            SOURCES_DIAG_C += $(SI4703_DIR)/si4703_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SI4703_COMMANDS),Y)
            MCAL_OPT += -DHAS_SI4703_COMMANDS
            SOURCES_C += $(SI4703_DIR)/si4703_commands.c
        endif
    endif

    ifeq ($(SPI),Y)
        include $(SI4703_DIR)/spi/si4703_spi.mk
    endif

    ifeq ($(I2C),Y)
        include $(SI4703_DIR)/i2c/si4703_i2c.mk
    endif

endif
