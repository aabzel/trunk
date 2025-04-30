
ifneq ($(LOG_MK_INC),Y)
    LOG_MK_INC=Y

    LOG_DIR = $(CONNECTIVITY_DIR)/log
    #@echo $(error LOG_DIR=$(LOG_DIR))
    INCDIR += -I$(LOG_DIR)
    #OPT += -Dio_printf=printf
    OPT += -DHAS_LOG

    SOURCES_C += $(LOG_DIR)/log.c

    ifeq ($(TABLE_UTILS),Y)
        OPT += -DHAS_TABLE_UTILS
        SOURCES_C += $(LOG_DIR)/table_utils.c
    endif
    
    ifeq ($(LOG_UTILS),Y)
        include $(LOG_DIR)/log_utils/log_utils.mk
    endif

    ifeq ($(LOG_TIME_STAMP),Y)
        OPT += -DHAS_LOG_TIME_STAMP
    endif

    ifeq ($(LOG_COLOR),Y)
        OPT += -DHAS_LOG_COLOR
    endif

    ifeq ($(STREAM),Y)
        OPT += -DHAS_STREAM
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LOG_DIAG),Y)
            OPT += -DHAS_LOG_DIAG
            SOURCES_C += $(LOG_DIR)/log_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LOG_COMMANDS),Y)
            OPT += -DHAS_LOG_COMMANDS
            OPT += -DHAS_LOG_EXT_CMD
            SOURCES_C += $(LOG_DIR)/log_commands.c
        endif
    endif
endif