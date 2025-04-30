$(info TIMER_MCAL_MK_INC=$(TIMER_MCAL_MK_INC) )

ifneq ($(TIMER_MCAL_MK_INC),Y)
    TIMER_MCAL_MK_INC=Y

    TIMER_MCAL_DIR = $(MCAL_COMMON_DIR)/timer
    # $(error TIMER_MCAL_DIR=[$(TIMER_MCAL_DIR)])

    OPT += -DHAS_TIMER
    INCDIR += -I$(TIMER_MCAL_DIR)

    SOURCES_C += $(TIMER_MCAL_DIR)/timer_common.c
    SOURCES_C += $(TIMER_MCAL_DIR)/timer_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(TIMER_DIAG),Y)
            #@echo $(error TIMER_DIAG=[$(TIMER_DIAG)])
            OPT += -DHAS_TIMER_DIAG
            SOURCES_C += $(TIMER_MCAL_DIR)/timer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TIMER_COMMANDS),Y)
            #@echo $(error TIMER_COMMANDS=[$(TIMER_COMMANDS)])
            OPT += -DHAS_TIMER_COMMANDS
            SOURCES_C += $(TIMER_MCAL_DIR)/timer_commands.c
        endif
    endif
endif






