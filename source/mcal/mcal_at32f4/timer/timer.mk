ifneq ($(TIMER_MCAL_AT32_MK_INC),Y)
    TIMER_MCAL_AT32_MK_INC=Y

    TIMER_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/timer
    #@echo $(error TIMER_CUSTOM_DIR=$(TIMER_CUSTOM_DIR))

    INCDIR += -I$(TIMER_CUSTOM_DIR)
    OPT += -DHAS_TIMER
    OPT += -DHAS_TIMER_CUSTOM

    SOURCES_C += $(TIMER_CUSTOM_DIR)/timer_mcal.c
    SOURCES_C += $(TIMER_CUSTOM_DIR)/timer_custom_isr.c

    ifeq ($(TIMER1),Y)
        OPT += -DHAS_TIMER1
    endif

    ifeq ($(TIMER2),Y)
        OPT += -DHAS_TIMER2
    endif

    ifeq ($(TIMER3),Y)
        OPT += -DHAS_TIMER3
    endif
    
    ifeq ($(TIMER4),Y)
        OPT += -DHAS_TIMER4
    endif
    
    ifeq ($(TIMER5),Y)
        OPT += -DHAS_TIMER5
    endif

    ifeq ($(TIMER6),Y)
        OPT += -DHAS_TIMER6
    endif
    
    ifeq ($(TIMER7),Y)
        OPT += -DHAS_TIMER7
    endif

    ifeq ($(TIMER8),Y)
        OPT += -DHAS_TIMER8
    endif
    
    ifeq ($(TIMER9),Y)
        OPT += -DHAS_TIMER9
    endif

    ifeq ($(TIMER10),Y)
        OPT += -DHAS_TIMER10
    endif

    ifeq ($(TIMER11),Y)
        OPT += -DHAS_TIMER11
    endif
    
    ifeq ($(TIMER12),Y)
        OPT += -DHAS_TIMER12
    endif
    
    ifeq ($(TIMER13),Y)
        OPT += -DHAS_TIMER13
    endif
    
    ifeq ($(TIMER14),Y)
        OPT += -DHAS_TIMER14
    endif

    ifeq ($(TIMER20),Y)
        OPT += -DHAS_TIMER20
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(TIMER_DIAG),Y)
            OPT += -DHAS_TIMER_DIAG
            SOURCES_C += $(TIMER_CUSTOM_DIR)/timer_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TIMER_COMMANDS),Y)
            #@echo $(error TIMER_COMMANDS=$(TIMER_COMMANDS))
            OPT += -DHAS_TIMER_COMMANDS
            SOURCES_C += $(TIMER_CUSTOM_DIR)/timer_custom_commands.c
        endif
    endif
endif
