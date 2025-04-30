$(info RISK_V_SELECT_MK_INC=$(RISK_V_SELECT_MK_INC) )
ifneq ($(RISK_V_SELECT_MK_INC),Y)
    RISK_V_SELECT_MK_INC=Y

    RISK_V_SEL_DIR = $(CORE_DIR)/rv32imc
    INCDIR += -I$(RISK_V_SEL_DIR)
    # $(error RISK_V_SEL_DIR=$(RISK_V_SEL_DIR))

    ifeq ($(SCR1_TIMER),Y)
        include $(RISK_V_SEL_DIR)/scr1_timer/scr1_timer.mk
    endif

    MICROCONTROLLER=Y
    SOURCES_C += $(RISK_V_SEL_DIR)/rv32imc_driver.c
    OPT += -DHAS_RISC_V
    OPT += -DHAS_RV32IMC
    
    ifeq ($(RV32IMC_EXT),Y)
        OPT += -DHAS_RV32IMC_EXT
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(RV32IMC_DIAG),Y)
            OPT += -DHAS_RV32IMC_DIAG
            SOURCES_C += $(RISK_V_SEL_DIR)/rv32imc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RV32IMC_COMMANDS),Y)
            OPT += -DHAS_RV32IMC_COMMANDS
            SOURCES_C += $(RISK_V_SEL_DIR)/rv32imc_commands.c
        endif
    endif

    MICROPROCESSOR += -march=rv32imc_zicsr_zifencei 
    MICROPROCESSOR += -mabi=ilp32 
    MICROPROCESSOR += -mstrict-align 
    MICROPROCESSOR += -msmall-data-limit=8
    MICROPROCESSOR += -mno-save-restore
    # MICROPROCESSOR += -mfloat-abi=soft
    # MICROPROCESSOR += -nostartfiles
    MICROPROCESSOR += -DMIK32V2
endif