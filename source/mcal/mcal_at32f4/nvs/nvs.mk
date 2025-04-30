
ifneq ($(NVS_CUSTOM_MK),Y)
    NVS_CUSTOM_MK=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    NVS_DIR = $(MCAL_AT32F4_DIR)/nvs
    #@echo $(error NVS_DIR=$(NVS_DIR))

    INCDIR += -I$(NVS_DIR)
    OPT += -DHAS_NVS

    NVS=Y
    SOURCES_C += $(NVS_DIR)/nvs_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(NVS_DIAG),Y)
            $(info Add NVS Custom diag)
            SOURCES_C += $(NVS_DIR)/nvs_custom_diag.c
        endif
    endif

    ifeq ($(NVS_WRITE),Y)
        $(info Add NVS write)
        #@echo $(error NVS_WRITE=$(NVS_WRITE))
        OPT += -DHAS_NVS_WRITE
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NVS_COMMANDS),Y)
            $(info Add NVS commands)
            SOURCES_C += $(NVS_DIR)/nvs_custom_commands.c
        endif
    endif
endif
