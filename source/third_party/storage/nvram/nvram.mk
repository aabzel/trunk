
ifneq ($(NVRAM_EHAL_MK_INC),Y)
    NVRAM_EHAL_MK_INC=Y
    
    NVRAM_EHAL_DIR = $(THIRD_PARTY_STORAGE_DIR)/nvram
    #@echo $(error NVRAM_EHAL_DIR= $(NVRAM_EHAL_DIR))
    INCDIR += -I$(NVRAM_EHAL_DIR)

    MCAL_OPT += -DHAS_NVRAM
    MCAL_OPT += -DNVRAM_IN_USE=ON

    ifeq ($(NVRAM_SET),Y)
        #@echo $(error NVRAM_SET= $(NVRAM_SET))
        MCAL_OPT += -DHAS_NVRAM_SET
    endif

    SOURCES_THIRD_PARTY_C+= $(NVRAM_EHAL_DIR)/nvram_drv.c
    SOURCES_THIRD_PARTY_C+= $(NVRAM_EHAL_DIR)/nvram_set_drv.c
    SOURCES_THIRD_PARTY_C+= $(NVRAM_EHAL_DIR)/nvram_configuration.c

    ifeq ($(DIAG),Y)
        ifeq ($(NVRAM_DIAG),Y)
            MCAL_OPT += -DHAS_NVRAM_DIAG
            MCAL_OPT += -DNVRAM_DIAG_IN_USE=ON
            SOURCES_THIRD_PARTY_C+= $(NVRAM_EHAL_DIR)/nvram_diagnostic.c
        endif
    endif


    ifeq ($(CLI),Y)
        ifeq ($(NVRAM_COMMANDS),Y)
            #@echo $(error NVRAM_COMMANDS=$(NVRAM_COMMANDS))
            MCAL_OPT += -DHAS_NVRAM_COMMANDS
            MCAL_OPT += -DHAS_NVRAM_CLI
            MCAL_OPT += -DNVRAM_CLI_IN_USE=ON
            SOURCES_THIRD_PARTY_C+= $(NVRAM_EHAL_DIR)/nvram_cli.c
        endif
    endif
endif