
$(info TIMER_CALC_MK_INC=$(TIMER_CALC_MK_INC))

ifneq ($(TIMER_CALC_MK_INC),Y)
    TIMER_CALC_MK_INC=Y

    $(info Build  + TIMER calculator)

    TIMER_CALC_DIR = $(COMPUTING_DIR)/timer_calc
    #@echo $(error TIMER_CALC_DIR=$(TIMER_CALC_DIR))
    COMPUTING=Y
    INCDIR += -I$(TIMER_CALC_DIR)

    SOURCES_C += $(TIMER_CALC_DIR)/timer_calc.c

    OPT += -DHAS_TIMER_CALC

    ifeq ($(DIAG),Y)
        ifeq ($(TIMER_CALC_DIAG),Y)
            OPT += -DHAS_TIMER_CALC_DIAG
            SOURCES_C += $(TIMER_CALC_DIR)/timer_calc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TIMER_CALC_COMMANDS),Y)
            #@echo $(error TIMER_CALC_COMMANDS=$(TIMER_CALC_COMMANDS))
            OPT += -DHAS_TIMER_CALC_COMMANDS
            SOURCES_C += $(TIMER_CALC_DIR)/timer_calc_commands.c
        endif
    endif
endif