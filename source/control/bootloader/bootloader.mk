
ifneq ($(BOOTLOADER_MAKE_INC),Y)
    BOOTLOADER_MAKE_INC=Y

    BOOTLOADER_DIR = $(CONTROL_DIR)/bootloader
    #@echo $(error BOOTLOADER_DIR=$(BOOTLOADER_DIR))

    INCDIR += -I$(BOOTLOADER_DIR)

    OPT += -DHAS_BOOTLOADER
    SOURCES_C += $(BOOTLOADER_DIR)/bootloader.c
    SOURCES_C += $(BOOTLOADER_DIR)/bootloader_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(BOOTLOADER_DIAG),Y)
            OPT += -DHAS_BOOTLOADER_DIAG
            SOURCES_C += $(BOOTLOADER_DIR)/bootloader_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BOOTLOADER_COMMANDS),Y)
            OPT += -DHAS_BOOTLOADER_COMMANDS
            SOURCES_C += $(BOOTLOADER_DIR)/bootloader_commands.c
        endif
    endif
endif