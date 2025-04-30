$(info USB_GENERAL_MK_INC=$(USB_GENERAL_MK_INC) )
ifneq ($(USB_GENERAL_MK_INC),Y)
    USB_GENERAL_MK_INC=Y
    $(info Build  $(mkfile_path))

    USB_GENERAL_DIR = $(MCAL_COMMON_DIR)/usb
    #@echo $(error USB_GENERAL_DIR=$(USB_GENERAL_DIR))

    INCDIR += -I$(USB_GENERAL_DIR)
    ifeq ($(USB_DEVICE),Y)
        ifeq ($(STREAM),Y)
            SOURCES_C += $(USB_GENERAL_DIR)/writer_usb_hid.c
        endif
    endif

    ifeq ($(CLI),Y)
        OPT += -DHAS_USB_COMMANDS
    endif

endif