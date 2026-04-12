ifneq ($(LOG_UTILS_MK_INC),Y)
    LOG_UTILS_MK_INC=Y

    LOG_UTILS_DIR = $(LOG_DIR)/log_utils

    # $(error LOG_UTILS_DIR=$(LOG_UTILS_DIR))
    INCDIR += -I$(LOG_UTILS_DIR)
    #MCAL_OPT += -Dcli_printf=printf
    MCAL_OPT += -DHAS_LOG_UTILS

    ifeq ($(STR2_DOUBLE),Y)
        MCAL_OPT += -DHAS_STR2_DOUBLE
    endif

    ifeq ($(STREAM),Y)
        # $(error STREAM=$(STREAM))
        SOURCES_C += $(LOG_UTILS_DIR)/log_utils.c
        SOURCES_C += $(LOG_UTILS_DIR)/oprintf.c
        SOURCES_C += $(LOG_UTILS_DIR)/print_format.c
    endif

    ifeq ($(CUSTOM_PRINTF),Y)
        MCAL_OPT += -DHAS_CUSTOM_PRINTF
    endif
endif