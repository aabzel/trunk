
$(info LED_RGB_MK_INC=$(LED_RGB_MK_INC))

ifneq ($(LED_RGB_MK_INC),Y)
    LED_RGB_MK_INC=Y

 
    $(info Add RGB LED)

    #FLASH_FS_DIR = $(WORKSPACE_LOC)Drivers/flash_fs
    #@echo $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    LED_RGB_DIR = $(LED_GENERAL_DIR)/led_rgb
    #@echo $(error LED_RGB_DIR=$(LED_RGB_DIR))

    INCDIR += -I$(LED_RGB_DIR)
    SOURCES_C += $(LED_RGB_DIR)/led_rgb_drv.c

    ifneq ($(LED),Y)
        @echo $(error Add General LED driver)
    endif

    LED_RGB=Y
    OPT += -DHAS_LED_RGB
    OPT += -DHAS_LED_RGB_PROC
    #MATH=Y

    ifeq ($(DIAG),Y)
        ifeq ($(LED_RGB_DIAG),Y)
            OPT += -DHAS_LED_RGB_DIAG
            OPT += -DHAS_LED_DIAG
            SOURCES_C += $(LED_RGB_DIR)/led_rgb_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LED_RGB_COMMANDS),Y)
            OPT += -DHAS_LED_RGB_COMMANDS
            SOURCES_C += $(LED_RGB_DIR)/led_rgb_commands.c
        endif
    endif
endif