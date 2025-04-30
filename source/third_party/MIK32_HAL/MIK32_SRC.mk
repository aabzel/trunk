
ifneq ($(MIK32_SRC_INC),Y) 
    MIK32_SRC_INC=Y

    THIRD_PARTY_DIR:= $(realpath $(THIRD_PARTY_DIR))

    HAL_MIK32_DIR += $(THIRD_PARTY_DIR)/MIK32_HAL
    # $(error HAL_MIK32_DIR=$(HAL_MIK32_DIR))

    HAL_MIK32_HAL_DIR = $(HAL_MIK32_DIR)/HAL
    HAL_MIK32_HAL_CORE_DIR = $(HAL_MIK32_HAL_DIR)/core
    HAL_MIK32_HAL_CORE_INC_DIR = $(HAL_MIK32_HAL_CORE_DIR)/Include

    HAL_MIK32_PERIPH_DIR = $(HAL_MIK32_HAL_DIR)/peripherals
    HAL_MIK32_PERIPH_SRC_DIR = $(HAL_MIK32_PERIPH_DIR)/Source
    HAL_MIK32_PERIPH_INCLUDE_DIR = $(HAL_MIK32_PERIPH_DIR)/Include

    HAL_MIK32_LL_DIR = $(HAL_MIK32_DIR)/LL
    HAL_MIK32_LL_CORE_DIR = $(HAL_MIK32_LL_DIR)/core
    HAL_MIK32_LL_PERIPHERY_DIR = $(HAL_MIK32_LL_DIR)/periphery


    INCDIR += -I$(HAL_MIK32_LL_DIR)
    INCDIR += -I$(HAL_MIK32_LL_CORE_DIR)
    INCDIR += -I$(HAL_MIK32_LL_PERIPHERY_DIR)
    INCDIR += -I$(HAL_MIK32_PERIPH_INCLUDE_DIR)
    INCDIR += -I$(HAL_MIK32_DIR)
    INCDIR += -I$(HAL_MIK32_HAL_DIR)
    INCDIR += -I$(HAL_MIK32_HAL_CORE_DIR)
    INCDIR += -I$(HAL_MIK32_HAL_CORE_INC_DIR)
    INCDIR += -I$(HAL_MIK32_PERIPH_DIR)
    INCDIR += -I$(HAL_MIK32_PERIPH_SRC_DIR)
    INCDIR += -I$(HAL_MIK32_HAL_DIR)/core/Include

    SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal.c
    SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal_pcc.c
    
    #C:/projects/code_base_debug/code_base_firmware/source/third_party/MIK32_HAL/HAL/peripherals/Source/mik32_hal_eeprom.c
    
                  #     /third_party/MIK32_HAL/HAL/core/Source/mik32_hal_scr1_timer.c
    #SOURCES_THIRD_PARTY_C += $(HAL_MIK32_HAL_CORE_DIR)/Source/mik32_hal_scr1_timer.c

    include $(HAL_MIK32_DIR)/SF/SF.mk

    ifeq ($(ADC),Y)
        $(info Add At ADC)
    endif

    ifeq ($(CLOCK),Y)
    endif


    ifeq ($(SPIFI),Y)
        SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal_spifi.c
        INCDIR += -I$(HAL_MIK32_HAL_DIR)/utilities/Include
        #SOURCES_THIRD_PARTY_C +=  $(HAL_MIK32_HAL_DIR)/utilities/Source/mik32_hal_spifi_w25.c
    endif
    
    ifeq ($(EEPROM),Y)
        SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal_eeprom.c
    endif

    ifeq ($(GPIO),Y)
        SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal_gpio.c
    endif

    ifeq ($(INTERRUPT),Y) 
        SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal_irq.c
    endif


    ifeq ($(NVS),Y) 
    endif

    ifeq ($(TIMER),Y) 
    endif

    ifeq ($(UART),Y)
        SOURCES_THIRD_PARTY_C += $(HAL_MIK32_PERIPH_SRC_DIR)/mik32_hal_usart.c
    endif

    ifeq ($(I2C),Y) 
    endif

    ifeq ($(RTC),Y) 
    endif

    ifeq ($(SPI),Y) 
    endif

    ifeq ($(QSPI),Y) 
    endif
endif