
$(info WIN_MK_INC=$(WIN_MK_INC))
ifneq ($(WIN_MK_INC),Y)
    WIN_MK_INC=Y

    WIN_UTILS_DIR =$(CONTROL_DIR)/win
    # $(error WIN_UTILS_DIR=$(WIN_UTILS_DIR))

    INCDIR += -I$(WIN_UTILS_DIR)

    MCAL_OPT += -DHAS_WIN_UTILS
    MCAL_OPT += -DHAS_PC
    MCAL_OPT += -DHAS_WIN
    
    ifeq ($(WIN_COLOR),Y)
        MCAL_OPT += -DHAS_WIN_COLOR
    endif
    
    ifeq ($(MINGW),Y)
        MCAL_OPT += -DHAS_MINGW
    endif

    SOURCES_C += $(WIN_UTILS_DIR)/win_utils.c

    #ifeq ($(SERIAL_PORT),Y)
        # $(error SERIAL_PORT=$(SERIAL_PORT))
        #MCAL_OPT += -DHAS_COM
        #MCAL_OPT += -DDEBUG_SERIAL
        #MCAL_OPT += -DHAS_SERIAL_PORT
        #MCAL_OPT += -DHAS_SERIAL
        # SOURCES_C += $(WIN_UTILS_DIR)/cli_wrappers.c
        # SOURCES_C += $(WIN_UTILS_DIR)/scan_serial_port.c
    #endif

    MCAL_OPT += -DHAS_PC_COMMANDS
    SOURCES_C += $(WIN_UTILS_DIR)/pc_commands.c

    ifeq ($(DIAG),Y)
        ifeq ($(WIN_DIAG),Y)
            # $(error DIAG_WIN=$(DIAG_WIN))
            MCAL_OPT += -DHAS_WIN_DIAG
            SOURCES_C += $(WIN_UTILS_DIR)/win_diag.c
        endif
    endif
endif
