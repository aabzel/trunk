ifneq ($(TP_LIS3DH_MK_INC),Y)
    TP_LIS3DH_MK_INC=Y

    TP_LIS3DH_DIR = $(THIRD_PARTY_ASICS_DIR)/lis3dh
    #@echo $(error TP_LIS3DH_DIR=$(TP_LIS3DH_DIR))

    INCDIR += -I$(TP_LIS3DH_DIR)

    OPT += -DHAS_LIS3DH_EHAL
    OPT += -DLIS3DH_IN_USE

    ifeq ($(LIS3DH_EHAL_PROC),Y)
        OPT += -DHAS_LIS3DH_EHAL_PROC
    endif

    SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_driver.c
    SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_miscellaneous.c
    SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_configuration.c
    
    ifeq ($(SPI),Y)
        SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_phy_spi.c
    endif
    
    ifeq ($(I2C),Y)
        SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_phy_i2c.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LIS3DH_EHAL_DIAG),Y)
            OPT += -DHAS_LIS3DH_DIAGNOSTIC
            SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_diagnostic.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LIS3DH_EHAL_COMMANDS),Y)
            OPT += -DHAS_LIS3DH_CLI
            SOURCES_THIRD_PARTY_C+= $(TP_LIS3DH_DIR)/lis3dh_cli.c
        endif
    endif
    
    # Autoformat index
    
    SOURCES_EHAL_C+= $(TP_LIS3DH_DIR)/lis3dh_driver.c
    SOURCES_EHAL_C+= $(TP_LIS3DH_DIR)/lis3dh_miscellaneous.c
    SOURCES_EHAL_C+= $(TP_LIS3DH_DIR)/lis3dh_configuration.c
    SOURCES_EHAL_C+= $(TP_LIS3DH_DIR)/lis3dh_cli.c
    SOURCES_EHAL_C+= $(TP_LIS3DH_DIR)/lis3dh_diagnostic.c
    
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_driver.h
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_miscellaneous.h
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_configuration.h
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_diagnostic.h
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_cli.h
    
    SOURCES_EHAL_C += $(TP_LIS3DH_DIR)/lis3dh_phy_spi.c
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_phy_spi.h
    
    SOURCES_EHAL_C += $(TP_LIS3DH_DIR)/lis3dh_phy_i2c.c
    SOURCES_EHAL_H += $(TP_LIS3DH_DIR)/lis3dh_phy_i2c.h
    

    # code style check index
    #https://habr.com/ru/articles/843746/

    SOURCES_CODE_STYLE_C += $(TP_LIS3DH_DIR)/lis3dh_phy_i2c.c
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_phy_i2c.h

    SOURCES_CODE_STYLE_C += $(TP_LIS3DH_DIR)/lis3dh_phy_spi.c
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_phy_spi.h
    
    
    SOURCES_CODE_STYLE_C += $(TP_LIS3DH_DIR)/lis3dh_driver.c
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_driver.h
    
    SOURCES_CODE_STYLE_C += $(TP_LIS3DH_DIR)/lis3dh_configuration.c
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_configuration.h
   
    SOURCES_CODE_STYLE_C += $(TP_LIS3DH_DIR)/lis3dh_miscellaneous.c
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_miscellaneous.h
    
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_constants.h
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_register_types.h
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_type.h
    SOURCES_CODE_STYLE_H += $(TP_LIS3DH_DIR)/lis3dh_dependencies.h
    
    
    #$(error SOURCES_EHAL_C=$(SOURCES_EHAL_C))
    
endif
