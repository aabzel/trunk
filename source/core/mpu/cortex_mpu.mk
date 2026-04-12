ifneq ($(CORTEX_MPU_CORTEX_M_MK_INC),Y)
    CORTEX_MPU_CORTEX_M_MK_INC=Y

    CORTEX_MPU_DIR = $(CORE_DIR)/mpu
    # $(error CORTEX_MPU_DIR=$(CORTEX_MPU_DIR))
    INCDIR += -I$(CORTEX_MPU_DIR)
    
    MPU_INTERRUPT=Y
    MCAL_OPT += -DHAS_CORTEX_MPU

    ifeq ($(MPU_INTERRUPT),Y)
        # $(error CORTEX_MPU_INTERRUPT=$(CORTEX_MPU_INTERRUPT))
        MCAL_OPT += -DHAS_CORTEX_MPU_INTERRUPT
        SOURCES_C += $(CORTEX_MPU_DIR)/cortex_mpu_isr.c
    endif

    SOURCES_C += $(CORTEX_MPU_DIR)/cortex_mpu.c

    ifeq ($(DIAG),Y)
        ifeq ($(MPU_DIAG),Y)
            # $(error MPU_DIAG=$(MPU_DIAG))
            MCAL_OPT += -DHAS_MPU_DIAG
            SOURCES_C += $(CORTEX_MPU_DIR)/cortex_mpu_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        # $(error CORTEX_MPU_COMMANDS=$(CORTEX_MPU_COMMANDS))
        ifeq ($(MPU_COMMANDS),Y)
            MCAL_OPT += -DHAS_MPU_COMMANDS
            SOURCES_C += $(CORTEX_MPU_DIR)/cortex_mpu_commands.c
        endif
    endif
endif
