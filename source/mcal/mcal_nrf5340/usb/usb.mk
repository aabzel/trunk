$(info USB_DRV_MK_INC=$(USB_DRV_MK_INC))

ifneq ($(USB_DRV_MK_INC),Y)
    USB_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    USB_DIR = $(MCAL_NRF5340_DIR)/usb
    #@echo $(error USB_DIR=$(USB_DIR))

    INCDIR += -I$(USB_DIR)
    OPT += -DHAS_USB

    SOURCES_C += $(USB_DIR)/usb_drv.c
    SOURCES_C += $(USB_DIR)/usb_config.c

    ifeq ($(USB_DEVICE),Y)
        include $(USB_DIR)/usb_device/usb_device.mk
    endif

    ifeq ($(CLI),Y)
        ifeq ($(USB_COMMANDS),Y)
            OPT += -DHAS_USB_COMMANDS
            SOURCES_C += $(USB_DIR)/usb_commands.c
        endif
    endif
endif
