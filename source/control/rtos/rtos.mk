$(info RTOS_MK_LOG=$(RTOS_MK_LOG))

ifneq ($(RTOS_MK_LOG),Y)
    RTOS_DRV_MK_LOG=Y

    RTOS_DRV_DIR = $(CONTROL_DIR)/rtos
    #@echo $(error RTOS_DRV_DIR= $(RTOS_DRV_DIR))

    INCDIR += -I$(RTOS_DRV_DIR)

    RTOS=Y
    OPT += -DHAS_RTOS

    SOURCES_C += $(RTOS_DRV_DIR)/rtos_drv.c

    ifeq ($(RTOS_DIAG),Y)
        OPT += -DHAS_RTOS_DIAG
        SOURCES_C += $(RTOS_DRV_DIR)/rtos_diag.c
    endif

    ifeq ($(RTOS_COMMANDS),Y)
        OPT += -DHAS_RTOS_COMMANDS
        #@echo $(error RTOS_COMMANDS= $(RTOS_COMMANDS))
        SOURCES_C +=  $(RTOS_DRV_DIR)/rtos_commands.c
    endif
endif