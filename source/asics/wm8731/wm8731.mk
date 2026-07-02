ifneq ($(WM8731_MK_INC),Y)
    WM8731_MK_INC=Y

    WM8731_DIR = $(ASICS_DIR)/wm8731
    #@echo $(error WM8731_DIR=$(WM8731_DIR))

    INCDIR += -I$(WM8731_DIR)

    MCAL_OPT += -DHAS_WM8731

    ifeq ($(WM8731_PROC),Y)
        MCAL_OPT += -DHAS_WM8731_PROC
    endif

    ifeq ($(WM8731_USB_MODE),Y)
        $(info +WM8731 USB mode)
        MCAL_OPT += -DHAS_WM8731_USB_MODE
    endif

    ifeq ($(WM8731_NORMAL_MODE),Y)
        $(info +WM8731 Normal mode)
        MCAL_OPT += -DHAS_WM8731_NORMAL_MODE
    endif

    ifeq ($(WM8731_VERIFY),Y)
        $(info +WM8731 test play)
        MCAL_OPT += -DHAS_WM8731_VERIFY
    endif

    SOURCES_C += $(WM8731_DIR)/wm8731_drv.c

    ifeq ($(WM8731_I2S_MASTER),Y)
        $(info Make WM8731 I2S Master)
        MCAL_OPT += -DHAS_WM8731_I2S_MASTER
        ifeq ($(I2S0_MASTER),Y)
            @echo $(error Double Master on I2S bus!)
        endif
    endif

    ifeq ($(WM8731_I2S_SLAVE),Y)
        $(info Make WM8731 I2S Slave)
        MCAL_OPT += -DHAS_WM8731_I2S_SLAVE
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(WM8731_DIAG),Y)
            $(info Add WM8731 Diag)
            MCAL_OPT += -DHAS_WM8731_DIAG
            SOURCES_C += $(WM8731_DIR)/wm8731_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(WM8731_COMMANDS),Y)
            #@echo $(error WM8731_COMMANDS=$(WM8731_COMMANDS))
            $(info Add WM8731 commands)
            MCAL_OPT += -DHAS_WM8731_COMMANDS
            MCAL_OPT += -DHAS_ASICS_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(WM8731_DIR)/wm8731_commands.c
        endif
    endif
endif
