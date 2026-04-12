ifneq ($(DISK_MK_INC),Y)
    DISK_MK_INC=Y

    DISK_DIR = $(STORAGE_DIR)/disk
    # $(error DISK_DIR=$(DISK_DIR))

    INCDIR += -I$(DISK_DIR)

    MCAL_OPT += -DHAS_DISK

    ifeq ($(DISK_PROC),Y)
        MCAL_OPT += -DHAS_DISK_PROC
    endif

    SOURCES_C += $(DISK_DIR)/disk.c

    ifeq ($(DISK_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_DISK_INTERRUPTS
        SOURCES_C += $(DISK_DIR)/disk_isr.c
    endif


    ifeq ($(DIAG),Y)
        ifeq ($(DISK_DIAG),Y)
            MCAL_OPT += -DHAS_DISK_DIAG
            SOURCES_C += $(DISK_DIR)/disk_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DISK_COMMANDS),Y)
            MCAL_OPT += -DHAS_DISK_COMMANDS
            SOURCES_C += $(DISK_DIR)/disk_commands.c
        endif
    endif
endif
