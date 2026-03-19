$(info USB_MCAL_MK_INC=$(USB_MCAL_MK_INC) )
ifneq ($(USB_MCAL_MK_INC),Y)
    USB_MCAL_MK_INC=Y

    USB_GENERAL_DIR = $(MCAL_COMMON_DIR)/usb
    # $(error USB_GENERAL_DIR=$(USB_GENERAL_DIR))

    INCDIR += -I$(USB_GENERAL_DIR)

    SOURCES_C += $(USB_GENERAL_DIR)/usb_general.c
    
    ifeq ($(USB_INTERRUPT),Y)
        MCAL_OPT += -DHAS_USB_INTERRUPT
    endif
    
    MCAL_OPT += -DHAS_USB
    MCAL_OPT += -DHAS_USB_PROC

    ifeq ($(USB_DEVICE),Y)
        MCAL_OPT += -DHAS_USB_DEVICE
    endif

    ifeq ($(USB_HS),Y)
        MCAL_OPT += -DHAS_USB_HS
    endif

    ifeq ($(USB_FS),Y)
        MCAL_OPT += -DHAS_USB_FS
    endif

    ifeq ($(CLI),Y)
        ifeq ($(USB_COMMANDS),Y)
            MCAL_OPT += -DHAS_USB_COMMANDS
            SOURCES_C += $(USB_GENERAL_DIR)/usb_commands.c
        endif
    endif

    
endif