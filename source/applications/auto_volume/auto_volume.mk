$(info AUTO_VOLUME_MK_LOG=$(AUTO_VOLUME_MK_LOG))

ifneq ($(AUTO_VOLUME_MK_LOG),Y)
    AUTO_VOLUME_DRV_MK_LOG=Y

    AUTO_VOLUME_DRV_DIR = $(APPLICATIONS_DIR)/auto_volume
    #@echo $(error AUTO_VOLUME_DRV_DIR= $(AUTO_VOLUME_DRV_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    INCDIR += -I$(AUTO_VOLUME_DRV_DIR)

    AUTO_VOLUME=Y
    OPT += -DHAS_AUTO_VOLUME
    OPT += -DHAS_AUTO_VOLUME_PROC

    SOURCES_C += $(AUTO_VOLUME_DRV_DIR)/auto_volume.c
    SOURCES_C += $(AUTO_VOLUME_DRV_DIR)/auto_volume_config.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_AUTO_VOLUME_DIAG
        SOURCES_C += $(AUTO_VOLUME_DRV_DIR)/auto_volume_diag.c
    endif

    ifeq ($(AUTO_VOLUME_COMMANDS),Y)
        OPT += -DHAS_AUTO_VOLUME_COMMANDS
        #@echo $(error AUTO_VOLUME_COMMANDS= $(AUTO_VOLUME_COMMANDS))
        SOURCES_C +=  $(AUTO_VOLUME_DRV_DIR)/auto_volume_commands.c
    endif
endif