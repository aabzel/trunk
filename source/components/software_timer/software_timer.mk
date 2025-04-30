$(info SOFTWARE_TIMER_MK_LOG=$(SOFTWARE_TIMER_MK_LOG))

ifneq ($(SOFTWARE_TIMER_MK_LOG),Y)
    SOFTWARE_TIMER_MK_LOG=Y
    SOFTWARE_TIMER_DIR = $(COMPONENTS_DIR)/software_timer
    #@echo $(error SOFTWARE_TIMER_DIR= $(SOFTWARE_TIMER_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    INCDIR += -I$(SOFTWARE_TIMER_DIR)

    SOFTWARE_TIMER=Y
    OPT += -DHAS_SOFTWARE_TIMER
    OPT += -DHAS_SOFTWARE_TIMER_PROC

    SOURCES_C += $(SOFTWARE_TIMER_DIR)/software_timer.c
    SOURCES_C += $(SOFTWARE_TIMER_DIR)/software_timer_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(SOFTWARE_TIMER_DIAG),Y)
            SOURCES_C += $(SOFTWARE_TIMER_DIR)/software_timer_diag.c
        endif
    endif

    ifeq ($(SOFTWARE_TIMER_COMMANDS),Y)
        OPT += -DHAS_SOFTWARE_TIMER_COMMANDS
        #@echo $(error SOFTWARE_TIMER_COMMANDS= $(SOFTWARE_TIMER_COMMANDS))
        SOURCES_C +=  $(SOFTWARE_TIMER_DIR)/software_timer_commands.c
    endif
endif