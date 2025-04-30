$(info FIR_MK_INC=$(FIR_MK_INC) )

ifneq ($(FIR_MK_INC),Y)
    FIR_MK_INC=Y

    FIR_DIR = $(DSP_DIR)/fir
    #@echo $(error FIR_DIR=[$(FIR_DIR)])
    INCDIR += -I$(FIR_DIR)

    OPT += -DHAS_FIR

    SOURCES_C += $(FIR_DIR)/fir.c
    SOURCES_C += $(FIR_DIR)/fir_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(FIR_DIAG),Y)
            OPT += -DHAS_FIR_DIAG
            SOURCES_C += $(FIR_DIR)/fir_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FIR_COMMANDS),Y)
            #@echo $(error FIR_COMMANDS=[$(FIR_COMMANDS)])
            OPT += -DHAS_FIR_COMMANDS
            SOURCES_C += $(FIR_DIR)/fir_commands.c
        endif
    endif
endif






