$(info USB_DEVICE_DRV_MK_INC=$(USB_DEVICE_DRV_MK_INC))

ifneq ($(USB_DEVICE_DRV_MK_INC),Y)
    USB_DEVICE_DRV_MK_INC=Y

    USB_DEVICE_DIR = $(USB_CUSTOM_DIR)/usb_device
    # $(error USB_DEVICE_DIR=$(USB_DEVICE_DIR))

    INCDIR += -I$(USB_DEVICE_DIR)

    SOURCES_C += $(USB_DEVICE_DIR)/usb_device.c

    ifeq ($(USB_DEVICE_DIAG),Y)
        SOURCES_C += $(USB_DEVICE_DIR)/usb_device_diag.c
    endif

    ifeq ($(USB_DEVICE_HS),Y)
        SOURCES_C += $(USB_DEVICE_DIR)/usbd_desc_hs.c
    endif

    ifeq ($(USB_DEVICE_FS),Y)
        #SOURCES_C += $(USB_DEVICE_DIR)/usbd_desc_fs.c
    endif

    ifeq ($(USB_DEVICE),Y)
        #INCDIR += -I$(USB_DEVICE_DIR)/Target
        #SOURCES_C += $(USB_DEVICE_DIR)/Target/usbd_conf.c
    endif

    #MCAL_OPT += -DUSB_OTG_HS_CORE
    ifeq ($(MSC),Y)
        MCAL_OPT += -DHAS_MSC
        MCAL_OPT += -DHAS_MASS_STORAGE_CLASS
        SOURCES_C += $(USB_DEVICE_DIR)/usbd_storage_if.c
    endif

    ifeq ($(MSC),Y)
        ifeq ($(HID),Y)
            MCAL_OPT += -DHAS_COMPOSIT_MSC_HID
            SOURCES_C += $(USB_DEVICE_DIR)/usbd_composit_msc_hid.c
        endif
    endif

    USB_DEVICE=Y
    MCAL_OPT += -DHAS_USB_DEVICE

    ifeq ($(HID),Y)
        MCAL_OPT += -DHAS_HID
        SOURCES_C += $(USB_DEVICE_DIR)/usbd_custom_hid_if.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(USB_DEVICE_COMMANDS),Y)
            MCAL_OPT += -DHAS_USB_DEVICE_COMMANDS
            SOURCES_C += $(USB_DEVICE_DIR)/usb_device_commands.c
        endif
    endif

    ifeq ($(USB_SERIAL),Y)
        # $(error USB_SERIAL=$(USB_SERIAL))
        include $(USB_DEVICE_DIR)/usb_serial/usb_serial.mk
    endif

endif
