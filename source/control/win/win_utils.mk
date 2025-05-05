
$(info WIN_MK_INC=$(WIN_MK_INC))
ifneq ($(WIN_MK_INC),Y)
    WIN_MK_INC=Y

    WIN_UTILS_DIR =$(CONTROL_DIR)/win
    #@echo $(error WIN_UTILS_DIR=$(WIN_UTILS_DIR))

    INCDIR += -I$(WIN_UTILS_DIR)

    OPT += -DHAS_WIN_UTILS
    OPT += -DHAS_PC
    OPT += -DHAS_WIN

    ifeq ($(MINGW),Y)
        OPT += -DHAS_MINGW
    endif

    SOURCES_C += $(WIN_UTILS_DIR)/win_utils.c

    ifeq ($(SERIAL_PORT),Y)
        #@echo $(error SERIAL_PORT=$(SERIAL_PORT))
        #OPT += -DHAS_COM
        #OPT += -DDEBUG_SERIAL
        #OPT += -DHAS_SERIAL_PORT
        #OPT += -DHAS_SERIAL
        #SOURCES_C += $(WIN_UTILS_DIR)/cli_wrappers.c
        #SOURCES_C += $(WIN_UTILS_DIR)/scan_serial_port.c
    endif

    OPT += -DHAS_PC_COMMANDS
    SOURCES_C += $(WIN_UTILS_DIR)/pc_commands.c

    ifeq ($(DIAG),Y)
        ifeq ($(WIN_DIAG),Y)
            #@echo $(error DIAG_WIN=$(DIAG_WIN))
            OPT += -DHAS_WIN_DIAG
            SOURCES_C += $(WIN_UTILS_DIR)/win_diag.c
        endif
    endif
endif
