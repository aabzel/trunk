$(info CLOCK_OUT_DRV_MK_INC=  $(CLOCK_OUT_DRV_MK_INC) )
ifneq ($(CLOCK_OUT_DRV_MK_INC),Y)
    CLOCK_OUT_DRV_MK_INC=Y

    CLOCK_OUT_DIR = $(MCAL_COMMON_DIR)/clock_out
    #@echo $(error CLOCK_OUT_DIR=$(CLOCK_OUT_DIR))

    INCDIR += -I$(CLOCK_OUT_DIR)

    MCAL_OPT += -DHAS_CLOCK_OUT
    SOURCES_C += $(CLOCK_OUT_DIR)/clock_out_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_OUT_DIAG),Y)
            MCAL_OPT += -DHAS_CLOCK_OUT_DIAG
            SOURCES_C += $(CLOCK_OUT_DIR)/clock_out_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_OUT_COMMANDS),Y)
            #@echo $(error CLOCK_OUT_COMMANDS=$(CLOCK_OUT_COMMANDS))
            MCAL_OPT += -DHAS_CLOCK_OUT_COMMANDS
            SOURCES_C += $(CLOCK_OUT_DIR)/clock_out_commands.c
        endif
    endif
endif