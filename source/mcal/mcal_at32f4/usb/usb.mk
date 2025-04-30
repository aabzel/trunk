$(info USB_DRV_MK_INC=$(USB_DRV_MK_INC))

ifneq ($(USB_DRV_MK_INC),Y)
    USB_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    USB_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/usb
    #@echo $(error USB_CUSTOM_DIR=$(USB_CUSTOM_DIR))

    INCDIR += -I$(USB_CUSTOM_DIR)
    OPT += -DHAS_USB

    SOURCES_C += $(USB_CUSTOM_DIR)/usb_drv.c

    ifeq ($(USB_HOST),Y)
        include $(USB_CUSTOM_DIR)/usb_host/usb_host.mk
    endif

    ifeq ($(USB_DEVICE),Y)
        include $(USB_CUSTOM_DIR)/usb_device/usb_device.mk
    endif

    ifeq ($(CLI),Y)
        ifeq ($(USB_COMMANDS),Y)
            OPT += -DHAS_USB_COMMANDS
            SOURCES_C += $(USB_CUSTOM_DIR)/usb_commands.c
        endif
    endif
endif
