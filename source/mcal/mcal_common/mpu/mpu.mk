ifneq ($(MPU_MK_INC),Y)
    MPU_MK_INC=Y

    MPU_DIR = $(MCAL_COMMON_DIR)/mpu
    # $(error MPU_DIR=$(MPU_DIR))

    INCDIR += -I$(MPU_DIR)

    MPU_PROC=Y
    MCAL_OPT += -DHAS_MPU

    ifeq ($(MPU_PROC),Y)
        MCAL_OPT += -DHAS_MPU_PROC
    endif

    SOURCES_C += $(MPU_DIR)/mpu_general.c

    ifeq ($(MPU_INTERRUPT),Y)
        MCAL_OPT += -DHAS_MPU_INTERRUPT
        SOURCES_C += $(MPU_DIR)/mpu_isr.c
    endif

    # must be outside
   # SOURCES_C += $(MPU_DIR)/mpu_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MPU_DIAG),Y)
            MCAL_OPT += -DHAS_MPU_DIAG
            SOURCES_C += $(MPU_DIR)/mpu_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MPU_COMMANDS),Y)
            MCAL_OPT += -DHAS_MPU_COMMANDS
            SOURCES_C += $(MPU_DIR)/mpu_commands.c
        endif
    endif
endif
