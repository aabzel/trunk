$(info MAILBOX_COMMON_MCAL_MK_INC=$(MAILBOX_COMMON_MCAL_MK_INC) )

ifneq ($(MAILBOX_COMMON_MCAL_MK_INC),Y)
    MAILBOX_COMMON_MCAL_MK_INC=Y

    MAILBOX_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/mailbox
    #@echo $(error MAILBOX_COMMON_MCAL_DIR=$(MAILBOX_COMMON_MCAL_DIR))

    INCDIR += -I$(MAILBOX_COMMON_MCAL_DIR)
    MCAL_OPT += -DHAS_MAILBOX
    MCAL_OPT += -DHAS_MAILBOX_PROC

    SOURCES_C += $(MAILBOX_COMMON_MCAL_DIR)/mailbox_general.c

    ifeq ($(MAILBOX_ISR),Y)
        MCAL_OPT += -DHAS_MAILBOX_ISR
        SOURCES_C += $(MAILBOX_COMMON_MCAL_DIR)/mailbox_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MAILBOX_DIAG),Y)
            MCAL_OPT += -DHAS_MAILBOX_DIAG
            SOURCES_C += $(MAILBOX_COMMON_MCAL_DIR)/mailbox_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAILBOX_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAILBOX_COMMANDS
            SOURCES_C += $(MAILBOX_COMMON_MCAL_DIR)/mailbox_commands.c
        endif
    endif    
endif