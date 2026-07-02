$(info USB_SERIAL_MK_INC=$(USB_SERIAL_MK_INC))

ifneq ($(USB_SERIAL_MK_INC),Y)
    USB_SERIAL_MK_INC=Y

    USB_SERIAL_DIR = $(USB_DEVICE_DIR)/usb_serial
    MCAL_OPT += -DHAS_USB_SERIAL
    # $(error USB_SERIAL_DIR=$(USB_SERIAL_DIR))

    INCDIR += -I$(USB_SERIAL_DIR)

    ifeq ($(USB_HS),Y)
        SOURCES_C += $(USB_SERIAL_DIR)/usbd_hs_desc_serial.c
        SOURCES_C += $(USB_SERIAL_DIR)/usbd_hs_cdc_if.c
    endif

    ifeq ($(USB_FS),Y)
        SOURCES_C += $(USB_SERIAL_DIR)/usbd_fs_desc_serial.c
        SOURCES_C += $(USB_SERIAL_DIR)/usbd_fs_cdc_if.c
    endif

    SOURCES_C += $(USB_SERIAL_DIR)/usbd_conf.c
    SOURCES_C += $(USB_SERIAL_DIR)/usb_serial.c

    ifeq ($(USB_SERIAL_DIAG),Y)
        MCAL_OPT += -DHAS_USB_SERIAL_DIAG
        SOURCES_C += $(USB_SERIAL_DIR)/usb_serial_diag.c
    endif
    
    SOURCES_C += $(USB_SERIAL_DIR)/usb_serial_commands.c
endif
