
ifneq ($(GENERAL_NVS_MK),Y)
    GENERAL_NVS_MK=Y

    GENERAL_NVS_DIR = $(MCAL_COMMON_DIR)/nvs
    #@echo $(error GENERAL_NVS_DIR=$(GENERAL_NVS_DIR))

    INCDIR += -I$(GENERAL_NVS_DIR)
    OPT += -DHAS_NVS

    ifeq ($(NVS_WRITE),Y)
        #@echo $(error NVS_WRITE=$(NVS_WRITE))
        OPT += -DHAS_NVS_WRITE
    endif

    SOURCES_C += $(GENERAL_NVS_DIR)/nvs_general_drv.c

    ifeq ($(NVS_DIAG),Y)
        #@echo $(error NVS_DIAG=$(NVS_DIAG))
        OPT += -DHAS_NVS_DIAG
        SOURCES_C += $(GENERAL_NVS_DIR)/nvs_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NVS_COMMANDS),Y)
            #@echo $(error NVS_COMMANDS=$(NVS_COMMANDS))
            OPT += -DHAS_NVS_COMMANDS
            SOURCES_C += $(GENERAL_NVS_DIR)/nvs_commands.c
        endif
    endif
endif
