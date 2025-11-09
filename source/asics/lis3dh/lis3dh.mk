ifneq ($(LIS3DH_MK_INC),Y)
    LIS3DH_MK_INC=Y

    LIS3DH_DIR = $(ASICS_DIR)/lis3dh
    #@echo $(error LIS3DH_DIR=$(LIS3DH_DIR))

    INCDIR += -I$(LIS3DH_DIR)

    OPT += -DHAS_LIS3DH

    ifeq ($(LIS3DH_PROC),Y)
        OPT += -DHAS_LIS3DH_PROC
    endif

    SOURCES_C += $(LIS3DH_DIR)/lis3dh_drv.c
    ifeq ($(I2C),Y)
        SOURCES_C += $(LIS3DH_DIR)/lis3dh_i2c.c
    endif

    ifeq ($(SPI),Y)
        SOURCES_C += $(LIS3DH_DIR)/lis3dh_spi.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LIS3DH_DIAG),Y)
            OPT += -DHAS_LIS3DH_DIAG
            SOURCES_C += $(LIS3DH_DIR)/lis3dh_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LIS3DH_COMMANDS),Y)
            OPT += -DHAS_LIS3DH_COMMANDS
            SOURCES_C += $(LIS3DH_DIR)/lis3dh_commands.c
        endif
    endif
endif
