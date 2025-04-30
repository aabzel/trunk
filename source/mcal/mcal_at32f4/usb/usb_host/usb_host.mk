$(info USB_HOST_DRV_MK_INC=$(USB_HOST_DRV_MK_INC))

ifneq ($(USB_HOST_DRV_MK_INC),Y)
    USB_HOST_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    USB_HOST_DIR = $(USB_CUSTOM_DIR)/usb_host
    #@echo $(error USB_HOST_DIR=$(USB_HOST_DIR))

    INCDIR += -I$(USB_HOST_DIR)
    INCDIR += -I$(USB_HOST_DIR)/Target

    #ifeq ($(USB_HOST_FS),Y)
    #    SOURCES_C += $(USB_HOST_DIR)/Target/usbh_fs_conf.c
    #endif

    #ifeq ($(USB_HOST_HS),Y)
    #    SOURCES_C += $(USB_HOST_DIR)/Target/usbh_hs_conf.c
    #endif
    SOURCES_C += $(USB_HOST_DIR)/Target/usbh_conf.c
    SOURCES_C += $(USB_HOST_DIR)/Target/usbh_platform.c

    SOURCES_C += $(USB_HOST_DIR)/usb_host.c

    USB=Y
    USB_HOST=Y
    OPT += -DHAS_USB_HOST

    ifeq ($(USB_HOST_PROC),Y)
        OPT += -DHAS_USB_HOST_PROC
    endif

    ifeq ($(KEYBOARD_FORWARDING),Y)
        OPT += -DHAS_KEYBOARD_FORWARDING
    endif

    ifeq ($(KEYBOARD_LOGING),Y)
        OPT += -DHAS_KEYBOARD_LOGING
    endif

    ifeq ($(HID),Y)
        OPT += -DHAS_HID
        SOURCES_C += $(USB_HOST_DIR)/usb_hid.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(USB_HOST_DIAG),Y)
            OPT += -DHAS_USB_HOST_DIAG
            SOURCES_C += $(USB_HOST_DIR)/usb_host_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(USB_HOST_COMMANDS),Y)
            OPT += -DHAS_USB_HOST_COMMANDS
            SOURCES_C += $(USB_HOST_DIR)/usb_host_commands.c
        endif
    endif
endif
