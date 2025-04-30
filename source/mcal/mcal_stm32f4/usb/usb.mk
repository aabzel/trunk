$(info USB_CUSTOM_DRV_MK_INC=$(USB_CUSTOM_DRV_MK_INC))

ifneq ($(USB_CUSTOM_DRV_MK_INC),Y)
    USB_CUSTOM_DRV_MK_INC=Y

    USB_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/usb
    #@echo $(error USB_CUSTOM_DIR=$(USB_CUSTOM_DIR))

    INCDIR += -I$(USB_CUSTOM_DIR)

    OPT += -DHAS_USB_CUSTOM
    
    SOURCES_C += $(USB_CUSTOM_DIR)/usb_mcal.c

    ifeq ($(USB_HOST),Y)
        #$(error USB_HOST=$(USB_HOST))
        #OPT += -DHAS_USB_HOST_COMMANDS
        include $(USB_CUSTOM_DIR)/usb_host/usb_host.mk
    endif

    ifeq ($(USB_DEVICE),Y)
        #$(error USB_DEVICE=$(USB_DEVICE))
        OPT += -DHAS_USB_DEVICE_COMMANDS
        include $(USB_CUSTOM_DIR)/usb_device/usb_device.mk
    endif

    ifeq ($(CLI),Y)
        ifeq ($(USB_COMMANDS),Y)
            #$(error USB_COMMANDS=$(USB_COMMANDS))
            OPT += -DHAS_USB_COMMANDS
            SOURCES_C += $(USB_CUSTOM_DIR)/usb_custom_commands.c
        endif
    endif
endif
