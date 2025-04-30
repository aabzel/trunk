
$(info DECIMATOR_MK_INC=$(DECIMATOR_MK_INC))

ifneq ($(DECIMATOR_MK_INC),Y)
    DECIMATOR_MK_INC=Y

    DECIMATOR_DIR = $(DSP_DIR)/decimator
    #@echo $(error DECIMATOR_DIR=$(DECIMATOR_DIR))

    INCDIR += -I$(DECIMATOR_DIR)
    SOURCES_C += $(DECIMATOR_DIR)/decimator.c
    #SOURCES_H += $(DECIMATOR_DIR)/decimator.h

    DECIMATOR=Y
    OPT += -DHAS_DECIMATOR

    ifeq ($(DIAG),Y)
        #@echo $(error DECIMATOR_DIAG=$(DECIMATOR_DIAG))
        OPT += -DHAS_DECIMATOR_DIAG
        SOURCES_C += $(DECIMATOR_DIR)/decimator_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DECIMATOR_COMMANDS),Y)
            OPT += -DHAS_DECIMATOR_COMMANDS
            SOURCES_C += $(DECIMATOR_DIR)/decimator_commands.c
        endif
    endif
endif