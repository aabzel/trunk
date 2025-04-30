$(info FREE_RTOS_MK_LOG=$(FREE_RTOS_MK_LOG))

ifneq ($(FREE_RTOS_MK_LOG),Y)
    FREE_RTOS_DRV_MK_LOG=Y

    FREE_RTOS_DRV_DIR = $(CONTROL_DIR)/free_rtos
    #@echo $(error FREE_RTOS_DRV_DIR= $(FREE_RTOS_DRV_DIR))

    INCDIR += -I$(FREE_RTOS_DRV_DIR)

    FREE_RTOS=Y
    OPT += -DHAS_FREE_RTOS
    OPT += -DHAS_RTOS_CUSTOM
    OPT += -DHAS_RTOS

    SOURCES_C += $(FREE_RTOS_DRV_DIR)/rtos_custom_drv.c

    ifeq ($(FREE_RTOS_DIAG),Y)
        OPT += -DHAS_FREE_RTOS_DIAG
        SOURCES_C += $(FREE_RTOS_DRV_DIR)/free_rtos_diag.c
    endif

    ifeq ($(FREE_RTOS_COMMANDS),Y)
        OPT += -DHAS_FREE_RTOS_COMMANDS
        #@echo $(error FREE_RTOS_COMMANDS= $(FREE_RTOS_COMMANDS))
        SOURCES_C +=  $(FREE_RTOS_DRV_DIR)/free_rtos_commands.c
    endif
endif