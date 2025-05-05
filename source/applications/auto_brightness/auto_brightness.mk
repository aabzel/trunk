$(info AUTO_BRIGHTNESS_MK_LOG=$(AUTO_BRIGHTNESS_MK_LOG))

ifneq ($(AUTO_BRIGHTNESS_MK_LOG),Y)
    AUTO_BRIGHTNESS_DRV_MK_LOG=Y

    AUTO_BRIGHTNESS_DRV_DIR = $(APPLICATIONS_DIR)/auto_brightness
    #@echo $(error AUTO_BRIGHTNESS_DRV_DIR= $(AUTO_BRIGHTNESS_DRV_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    INCDIR += -I$(AUTO_BRIGHTNESS_DRV_DIR)

    AUTO_BRIGHTNESS=Y
    OPT += -DHAS_AUTO_BRIGHTNESS
    OPT += -DHAS_AUTO_BRIGHTNESS_PROC

    SOURCES_C += $(AUTO_BRIGHTNESS_DRV_DIR)/auto_brightness.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_AUTO_BRIGHTNESS_DIAG
        SOURCES_C += $(AUTO_BRIGHTNESS_DRV_DIR)/auto_brightness_diag.c
    endif

    ifeq ($(AUTO_BRIGHTNESS_COMMANDS),Y)
        OPT += -DHAS_AUTO_BRIGHTNESS_COMMANDS
        #@echo $(error AUTO_BRIGHTNESS_COMMANDS= $(AUTO_BRIGHTNESS_COMMANDS))
        SOURCES_C +=  $(AUTO_BRIGHTNESS_DRV_DIR)/auto_brightness_commands.c
    endif
endif