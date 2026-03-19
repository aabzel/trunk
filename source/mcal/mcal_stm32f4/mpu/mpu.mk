$(info MPU_CUSTOM_MK_INC=$(MPU_CUSTOM_MK_INC) )
ifneq ($(MPU_CUSTOM_MK_INC),Y)
    MPU_CUSTOM_MK_INC=Y

    MPU_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/mpu

    INCDIR += -I$(MPU_CUSTOM_DIR)

    SOURCES_C += $(MPU_CUSTOM_DIR)/mpu_mcal.c

    MCAL_OPT += -DHAS_MPU_CUSTOM

    
    ifeq ($(MPU_INTERRUPT),Y)
        MCAL_OPT += -DHAS_MPU_INTERRUPT
        SOURCES_C += $(MPU_CUSTOM_DIR)/mpu_custom_isr.c
    endif

    ifeq ($(MPU0),Y)
        MCAL_OPT += -DHAS_MPU0
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MPU_DIAG),Y)
            MCAL_OPT += -DHAS_MPU_CUSTOM_DIAG
            SOURCES_C += $(MPU_CUSTOM_DIR)/mpu_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MPU_COMMANDS),Y)
            MCAL_OPT += -DHAS_MPU_CUSTOM_COMMANDS
            SOURCES_C += $(MPU_CUSTOM_DIR)/mpu_custom_commands.c
        endif
    endif
endif