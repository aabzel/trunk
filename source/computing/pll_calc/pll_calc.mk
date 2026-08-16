
$(info PLL_CALC_MK_INC=$(PLL_CALC_MK_INC))

ifneq ($(PLL_CALC_MK_INC),Y)
    PLL_CALC_MK_INC=Y

    PLL_CALC_DIR = $(COMPUTING_DIR)/pll_calc
    # $(error PLL_CALC_DIR=$(PLL_CALC_DIR))
    COMPUTING=Y
    INCDIR += -I$(PLL_CALC_DIR)
    MCAL_OPT += -DHAS_PLL_CALC

    SOURCES_C += $(PLL_CALC_DIR)/pll_calc.c

    ifeq ($(CAN),Y)
        SOURCES_C += $(PLL_CALC_DIR)/can_segments_stm32.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(PLL_CALC_DIAG),Y)
            MCAL_OPT += -DHAS_PLL_CALC_DIAG
            SOURCES_DIAG_C += $(PLL_CALC_DIR)/pll_calc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PLL_CALC_COMMANDS),Y)
            # $(error PLL_CALC_COMMANDS=$(PLL_CALC_COMMANDS))
            MCAL_OPT += -DHAS_PLL_CALC_COMMANDS
            SOURCES_C += $(PLL_CALC_DIR)/pll_calc_commands.c
        endif
    endif
endif