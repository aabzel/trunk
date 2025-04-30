
$(info PHOTORESISTOR_MK_INC=$(PHOTORESISTOR_MK_INC))

ifneq ($(PHOTORESISTOR_MK_INC),Y)
    PHOTORESISTOR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    $(info Build  Add voltage divider)

    PHOTORESISTOR_DIR = $(SENSITIVITY_DIR)/photoresistor
    #@echo $(error PHOTORESISTOR_DIR=$(PHOTORESISTOR_DIR))

    INCDIR += -I$(PHOTORESISTOR_DIR)

    SOURCES_C += $(PHOTORESISTOR_DIR)/photoresistor.c

    OPT += -DHAS_PHOTORESISTOR

    ifeq ($(DIAG),Y)
        ifeq ($(PHOTORESISTOR_DIAG),Y)
            OPT += -DHAS_PHOTORESISTOR_DIAG
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PHOTORESISTOR_COMMANDS),Y)
            OPT += -DHAS_PHOTORESISTOR_COMMANDS
            SOURCES_C += $(PHOTORESISTOR_DIR)/photoresistor_commands.c
        endif
    endif
endif