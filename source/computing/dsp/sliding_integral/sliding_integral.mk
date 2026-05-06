$(info SLIDING_INTEGRAL_MK_INC=$(SLIDING_INTEGRAL_MK_INC) )

ifneq ($(SLIDING_INTEGRAL_MK_INC),Y)
    SLIDING_INTEGRAL_MK_INC=Y

    SLIDING_INTEGRAL_DIR = $(DSP_DIR)/sliding_integral
    #@echo $(error SLIDING_INTEGRAL_DIR=[$(SLIDING_INTEGRAL_DIR)])
    INCDIR += -I$(SLIDING_INTEGRAL_DIR)

    MCAL_OPT += -DHAS_SLIDING_INTEGRAL

    SOURCES_C += $(SLIDING_INTEGRAL_DIR)/sliding_integral.c

    ifeq ($(DIAG),Y)
        ifeq ($(SLIDING_INTEGRAL_DIAG),Y)
            MCAL_OPT += -DHAS_SLIDING_INTEGRAL_DIAG
            SOURCES_C += $(SLIDING_INTEGRAL_DIR)/sliding_integral_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SLIDING_INTEGRAL_COMMANDS),Y)
            #@echo $(error SLIDING_INTEGRAL_COMMANDS=[$(SLIDING_INTEGRAL_COMMANDS)])
            MCAL_OPT += -DHAS_SLIDING_INTEGRAL_COMMANDS
            SOURCES_C += $(SLIDING_INTEGRAL_DIR)/sliding_integral_commands.c
        endif
    endif
endif






