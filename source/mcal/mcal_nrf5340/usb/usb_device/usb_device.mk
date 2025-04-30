$(info USB_DEVICE_DRV_MK_INC=$(USB_DEVICE_DRV_MK_INC))

ifneq ($(USB_DEVICE_DRV_MK_INC),Y)
    USB_DEVICE_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    USB_DEVICE_DIR = $(WORKSPACE_LOC)bsp/bsp_nrf5340/usb/usb_device
    #@echo $(error USB_DEVICE_DIR=$(USB_DEVICE_DIR))

    INCDIR += -I$(USB_DEVICE_DIR)

    SOURCES_C += $(USB_DEVICE_DIR)/usb_device.c

    USB_DEVICE=Y
    OPT += -DHAS_USB_DEVICE


    ifeq ($(CLI),Y)
        ifeq ($(USB_DEVICE_COMMANDS),Y)
            OPT += -DHAS_USB_DEVICE_COMMANDS
            SOURCES_C += $(USB_DEVICE_DIR)/usb_device_commands.c
        endif
    endif

    #include $(USB_DEVICE_DIR)/app/usb_app.mk

endif
