ifneq ($(SI4737_MK_INC),Y)
    SI4737_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    SI4737_DIR = $(ASICS_DIR)/si4737
    #@echo $(error SI4737_DIR=$(SI4737_DIR))

    INCDIR += -I$(SI4737_DIR)

    MCAL_OPT += -DHAS_SI4737
    MCAL_OPT += -DHAS_MULTIMEDIA
    RDS=Y

    FM_TUNER=Y
    ifeq ($(FM_TUNER),Y)
        MCAL_OPT += -DHAS_FM_TUNER
    endif
    
    SOURCES_C += $(SI4737_DIR)/si4737_drv.c
    SOURCES_C += $(SI4737_DIR)/si4737_config.c
    SOURCES_C += $(SI4737_DIR)/radio_stations_rus.c

    ifeq ($(RDS),Y)
        MCAL_OPT += -DHAS_RDS
        SOURCES_C += $(SI4737_DIR)/si4737_rds_drv.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SI4737_DIAG),Y)
            SOURCES_C += $(SI4737_DIR)/si4737_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SI4737_COMMANDS),Y)
            MCAL_OPT += -DHAS_SI4737_COMMANDS
            SOURCES_C += $(SI4737_DIR)/si4737_commands.c
        endif
    endif

endif
