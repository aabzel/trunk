$(info LTR390_DRIVER_INC=$(LTR390_DRIVER_INC) )

ifneq ($(LTR390_DRIVER_INC),Y)
    LTR390_DRIVER_INC=Y
    LTR390_DIR = $(ASICS_DIR)/ltr390
    #@echo $(error LTR390_DIR=$(LTR390_DIR))
    $(info + LTR390)

    INCDIR += -I$(LTR390_DIR)
    MCAL_OPT += -DHAS_LTR390
    MCAL_OPT += -DHAS_LTR390_PROC
    MCAL_OPT += -DHAS_LTR390_INIT

    SOURCES_C += $(LTR390_DIR)/ltr390_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(LTR390_DIAG),Y)
            $(info Add LTR390_DIAG)
            MCAL_OPT += -DHAS_LTR390_DIAG
            SOURCES_C += $(LTR390_DIR)/ltr390_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LTR390_COMMANDS),Y)
            #@echo $(error LTR390_COMMANDS=$(LTR390_COMMANDS))
            $(info Add LTR390_COMMANDS)
            MCAL_OPT += -DHAS_LTR390_COMMANDS
            SOURCES_C += $(LTR390_DIR)/ltr390_commands.c
        endif
    endif
endif
