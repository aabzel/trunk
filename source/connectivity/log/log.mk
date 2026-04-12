ifneq ($(LOG_MK_INC),Y)
    LOG_MK_INC=Y

    LOG_DIR = $(CONNECTIVITY_DIR)/log
    # $(error LOG_DIR=$(LOG_DIR))
    #MCAL_OPT += -Dio_printf=printf
    INCDIR += -I$(LOG_DIR)
    MCAL_OPT += -DHAS_LOG

    SOURCES_C += $(LOG_DIR)/log.c

    ifeq ($(LOG_DISABLE),Y)
        MCAL_OPT += -DHAS_LOG_DISABLE
    endif

    ifeq ($(TABLE_UTILS),Y)
        MCAL_OPT += -DHAS_TABLE_UTILS
        # $(error TABLE_UTILS=$(TABLE_UTILS))
        SOURCES_C += $(LOG_DIR)/table_utils.c
    endif

    ifeq ($(WRITER),Y)
        include $(LOG_DIR)/writer/writer.mk
    endif

    ifeq ($(LOG_UTILS),Y)
        include $(LOG_DIR)/log_utils/log_utils.mk
    endif

    ifeq ($(LOG_TIME_STAMP),Y)
        MCAL_OPT += -DHAS_LOG_TIME_STAMP
    endif

    ifeq ($(LOG_COLOR),Y)
        MCAL_OPT += -DHAS_LOG_COLOR
    endif

    ifeq ($(STREAM),Y)
        MCAL_OPT += -DHAS_STREAM
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LOG_DIAG),Y)
            MCAL_OPT += -DHAS_LOG_DIAG
            SOURCES_DIAG_C += $(LOG_DIR)/log_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LOG_COMMANDS),Y)
            MCAL_OPT += -DHAS_LOG_COMMANDS
            MCAL_OPT += -DHAS_LOG_EXT_CMD
            SOURCES_C += $(LOG_DIR)/log_commands.c
        endif
    endif
endif