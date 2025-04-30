$(info PID_MK_INC=$(PID_MK_INC) )
ifneq ($(PID_MK_INC),Y)
    PID_MK_INC=Y

    $(info + PID)

    PID_DIR = $(CONTROL_DIR)/pid
    #@echo $(error PID_DIR=$(PID_DIR))

    OPT += -DHAS_PID

    ifeq ($(PID_PROC),Y)
        OPT += -DHAS_PID_PROC
    endif

    INCDIR += -I$(PID_DIR)

    SOURCES_C += $(PID_DIR)/pid.c

    ifeq ($(DIAG),Y)
        ifeq ($(PID_DIAG),Y)
            $(info + PID DIAG)
            OPT += -DHAS_PID_DIAG
            SOURCES_C += $(PID_DIR)/pid_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PID_COMMANDS),Y)
            OPT += -DHAS_PID_COMMANDS
            SOURCES_C += $(PID_DIR)/pid_commands.c
        endif
    endif
endif