
ifneq ($(BOOT_DRV_MK_INC),Y)
    BOOT_DRV_MK_INC=Y

    BOOT_DRV_DIR = $(CONTROL_DIR)/boot_drv

    INCDIR += -I$(BOOT_DRV_DIR)

    OPT += -DHAS_BOOT
    SOURCES_C += $(BOOT_DRV_DIR)/boot_driver.c

    ifeq ($(DIAG),Y)
        #$(error DIAG=$(DIAG))
        ifeq ($(BOOT_DIAG),Y)
            OPT += -DHAS_BOOT_DIAG
            SOURCES_C += $(BOOT_DRV_DIR)/boot_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BOOT_COMMANDS),Y)
            OPT += -DHAS_BOOT_COMMANDS
            SOURCES_C += $(BOOT_DRV_DIR)/boot_commands.c
        endif
    endif
endif