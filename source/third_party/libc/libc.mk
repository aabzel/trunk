ifneq ($(LIBC_MK_INC),Y)
    LIBC_MK_INC=Y

    LIBC_DIR += $(THIRD_PARTY_DIR)/libc

    #$(error LIBC_DIR= $(LIBC_DIR))
    INCDIR += -I$(LIBC_DIR)

    ifeq ($(XPRINTF),Y)
        include $(LIBC_DIR)/xprintf/xprintf.mk
    endif
endif