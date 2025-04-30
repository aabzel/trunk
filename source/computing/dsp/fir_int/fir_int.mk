$(info FIR_INT_MK_INC=$(FIR_INT_MK_INC) )

ifneq ($(FIR_INT_MK_INC),Y)
    FIR_INT_MK_INC=Y

    FIR_INT_DIR = $(DSP_DIR)/fir_int
    #@echo $(error FIR_INT_DIR=[$(FIR_INT_DIR)])
    INCDIR += -I$(FIR_INT_DIR)

    OPT += -DHAS_FIR_INT

    SOURCES_C += $(FIR_INT_DIR)/fir_int.c

    ifeq ($(DIAG),Y)
        ifeq ($(FIR_INT_DIAG),Y)
            OPT += -DHAS_FIR_INT_DIAG
            SOURCES_C += $(FIR_INT_DIR)/fir_int_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FIR_INT_COMMANDS),Y)
            #@echo $(error FIR_INT_COMMANDS=[$(FIR_INT_COMMANDS)])
            OPT += -DHAS_FIR_INT_COMMANDS
            SOURCES_C += $(FIR_INT_DIR)/fir_int_commands.c
        endif
    endif
endif






