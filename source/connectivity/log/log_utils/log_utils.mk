ifneq ($(LOG_UTILS_MK_INC),Y)
    LOG_UTILS_MK_INC=Y


    LOG_UTILS_DIR = $(LOG_DIR)/log_utils

    # $(error LOG_UTILS_DIR=$(LOG_UTILS_DIR))
    INCDIR += -I$(LOG_UTILS_DIR)
    #OPT += -Dcli_printf=printf
    OPT += -DHAS_LOG_UTILS
    
    ifeq ($(STR2_DOUBLE),Y)
        OPT += -DHAS_STR2_DOUBLE
    endif
    
    ifeq ($(STREAM),Y)
        #@echo $(error STREAM=$(STREAM))
        SOURCES_C += $(LOG_UTILS_DIR)/log_utils.c
        SOURCES_C += $(LOG_UTILS_DIR)/oprintf.c
        SOURCES_C += $(LOG_UTILS_DIR)/ostream.c
        SOURCES_C += $(LOG_UTILS_DIR)/print_format.c
        SOURCES_C += $(LOG_UTILS_DIR)/string_writer.c
        SOURCES_C += $(LOG_UTILS_DIR)/writer_generic.c
        SOURCES_C += $(LOG_UTILS_DIR)/writer_config.c
    endif

    ifeq ($(UART),Y)
        #@echo $(error UART= $(UART))
        SOURCES_C += $(LOG_UTILS_DIR)/writer_uart.c
    endif

    ifeq ($(CUSTOM_PRINTF),Y)
        OPT += -DHAS_CUSTOM_PRINTF
    endif

    ifeq ($(X86),Y)
        SOURCES_C += $(LOG_UTILS_DIR)/writer_stdout.c
    endif
    
endif