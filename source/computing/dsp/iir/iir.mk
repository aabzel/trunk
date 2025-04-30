$(info IIR_MK_INC=$(IIR_MK_INC) )

ifneq ($(IIR_MK_INC),Y)
    IIR_MK_INC=Y

    IIR_DIR = $(DSP_DIR)/iir
    #@echo $(error IIR_DIR=[$(IIR_DIR)])
    INCDIR += -I$(IIR_DIR)

    OPT += -DHAS_IIR
    SOURCES_C += $(IIR_DIR)/iir.c
    SOURCES_C += $(IIR_DIR)/iir_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(IIR_DIAG),Y)
            OPT += -DHAS_IIR_DIAG
            SOURCES_C += $(IIR_DIR)/iir_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(IIR_COMMANDS),Y)
            #@echo $(error IIR_COMMANDS=[$(IIR_COMMANDS)])
            OPT += -DHAS_IIR_COMMANDS
            SOURCES_C += $(IIR_DIR)/iir_commands.c
        endif
    endif
endif






