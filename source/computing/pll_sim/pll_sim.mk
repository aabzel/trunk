
$(info PLL_SIM_MK_INC=$(PLL_SIM_MK_INC))

ifneq ($(PLL_SIM_MK_INC),Y)
    PLL_SIM_MK_INC=Y

    PLL_SIM_DIR = $(COMPUTING_DIR)/pll_sim
    #@echo $(error PLL_SIM_DIR = $(PLL_SIM_DIR))

    OPT += -DHAS_PLL_SIM
    OPT += -DHAS_PLL_SIM_PROC
    
    INCDIR += -I$(PLL_SIM_DIR)

    SOURCES_C += $(PLL_SIM_DIR)/pll_sim.c


    ifeq ($(DIAG),Y)
        ifeq ($(PLL_SIM_DIAG),Y)
            OPT += -DHAS_PLL_SIM_DIAG
            SOURCES_C += $(PLL_SIM_DIR)/pll_sim_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PLL_SIM_COMMANDS),Y)
            #@echo $(error PLL_SIM_COMMANDS = $(PLL_SIM_COMMANDS))
            OPT += -DHAS_PLL_SIM_COMMANDS
            SOURCES_C += $(PLL_SIM_DIR)/pll_sim_commands.c
        endif
    endif
endif
