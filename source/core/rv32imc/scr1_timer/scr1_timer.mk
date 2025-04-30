ifneq ($(SCR1_TIMER_MK_INC),Y)
    SCR1_TIMER_MK_INC=Y

    $(info Build  $(mkfile_path) )

    SCR1_TIMER_DIR = $(RISK_V_SEL_DIR)/scr1_timer
   # $(error SCR1_TIMER_DIR=$(SCR1_TIMER_DIR))
    INCDIR += -I$(SCR1_TIMER_DIR)
    OPT += -DHAS_SCR1_TIMER
    OPT += -DHAS_SYSTIC_INT
    OPT += -DHAS_SCR1_TIMER_ISR

    SOURCES_C += $(SCR1_TIMER_DIR)/scr1_timer_config.c
    SOURCES_C += $(SCR1_TIMER_DIR)/scr1_timer.c

    ifeq ($(DIAG),Y)
        ifeq ($(SCR1_TIMER_DIAG),Y)
            # $(error SCR1_TIMER_DIAG=$(SCR1_TIMER_DIAG))
            OPT += -DHAS_SCR1_TIMER_DIAG
            SOURCES_C += $(SCR1_TIMER_DIR)/scr1_timer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        # $(error CLI=$(CLI))
        ifeq ($(SCR1_TIMER_COMMANDS),Y)
            OPT += -DHAS_SCR1_TIMER_COMMANDS
            SOURCES_C += $(SCR1_TIMER_DIR)/scr1_timer_commands.c
        endif
    endif
endif