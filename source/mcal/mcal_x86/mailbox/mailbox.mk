$(info MAILBOX_CUSTOM_MK_INC=$(MAILBOX_CUSTOM_MK_INC) )

ifneq ($(MAILBOX_CUSTOM_MK_INC),Y)
    MAILBOX_CUSTOM_MK_INC=Y

    MAILBOX_CUSTOM_DIR = $(MCAL_X86_DIR)/mailbox
    #@echo $(error MAILBOX_CUSTOM_DIR=$(MAILBOX_CUSTOM_DIR))

    INCDIR += -I$(MAILBOX_CUSTOM_DIR)

    SOURCES_C += $(MAILBOX_CUSTOM_DIR)/mailbox_mcal.c
    MCAL_OPT += -DHAS_MAILBOX_CUSTOM

    ifeq ($(MAILBOX_ISR),Y)
        $(info + MAILBOX ISR )
        MCAL_OPT += -DHAS_MAILBOX_ISR
        SOURCES_C += $(MAILBOX_CUSTOM_DIR)/mailbox_custom_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MAILBOX_DIAG),Y)
            MCAL_OPT += -DHAS_MAILBOX_CUSTOM_DIAG
            SOURCES_C += $(MAILBOX_CUSTOM_DIR)/mailbox_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAILBOX_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAILBOX_CUSTOM_COMMANDS
            SOURCES_C += $(MAILBOX_CUSTOM_DIR)/mailbox_custom_commands.c
        endif
    endif
endif