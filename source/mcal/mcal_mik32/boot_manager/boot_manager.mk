$(info BOOT_MANAGER_DRV_MK_INC=  $(BOOT_MANAGER_DRV_MK_INC) )
ifneq ($(BOOT_MANAGER_DRV_MK_INC),Y)
    BOOT_MANAGER_DRV_MK_INC=Y

    BOOT_MANAGER_MIK_DIR = $(MCAL_MIK32_DIR)/boot_manager
    #@echo $(error BOOT_MANAGER_MIK_DIR=$(BOOT_MANAGER_MIK_DIR))

    INCDIR += -I$(BOOT_MANAGER_MIK_DIR)
    OPT += -DHAS_BOOT_MANAGER

    SOURCES_C += $(BOOT_MANAGER_MIK_DIR)/boot_manager.c

    ifeq ($(DIAG),Y)
        ifeq ($(BOOT_MANAGER_DIAG),Y)
            OPT += -DHAS_BOOT_MANAGER_DIAG
            SOURCES_C += $(BOOT_MANAGER_MIK_DIR)/boot_manager_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BOOT_MANAGER_COMMANDS),Y)
            #@echo $(error BOOT_MANAGER_COMMANDS=$(BOOT_MANAGER_COMMANDS))
            OPT += -DHAS_BOOT_MANAGER_COMMANDS
            SOURCES_C += $(BOOT_MANAGER_MIK_DIR)/boot_manager_commands.c
        endif
    endif
endif