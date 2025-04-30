ifneq ($(XPRINTF_MK_INC),Y)
    XPRINTF_MK_INC=Y

    XPRINTF_DIR += $(LIBC_DIR)/xprintf

    # $(error XPRINTF_DIR= $(XPRINTF_DIR))
    INCDIR += -I$(XPRINTF_DIR)

    OPT += -DXF_USE_OUTPUT
    OPT += -DXF_USE_FP
    OPT += -DXF_USE_INPUT
    OPT += -DXF_USE_LLI
    OPT += -DXF_USE_DUMP
    SOURCES_THIRD_PARTY_C += $(XPRINTF_DIR)/xprintf.c
endif