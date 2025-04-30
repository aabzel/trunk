
$(info PLL_CALC_MK_INC=$(PLL_CALC_MK_INC))

ifneq ($(PLL_CALC_MK_INC),Y)
    PLL_CALC_MK_INC=Y

    $(info Build  + PLL calculator)

    PLL_CALC_DIR = $(COMPUTING_DIR)/pll_calc
    #@echo $(error PLL_CALC_DIR=$(PLL_CALC_DIR))
    COMPUTING=Y
    INCDIR += -I$(PLL_CALC_DIR)

    SOURCES_C += $(PLL_CALC_DIR)/pll_calc.c

    OPT += -DHAS_PLL_CALC

    ifeq ($(DIAG),Y)
        ifeq ($(PLL_CALC_DIAG),Y)
            OPT += -DHAS_PLL_CALC_DIAG
            SOURCES_C += $(PLL_CALC_DIR)/pll_calc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PLL_CALC_COMMANDS),Y)
            #@echo $(error PLL_CALC_COMMANDS=$(PLL_CALC_COMMANDS))
            OPT += -DHAS_PLL_CALC_COMMANDS
            SOURCES_C += $(PLL_CALC_DIR)/pll_calc_commands.c
        endif
    endif
endif