$(info SW_NVRAM_MK_INC=$(SW_NVRAM_MK_INC))
ifneq ($(SW_NVRAM_MK_INC),Y)
    SW_NVRAM_MK_INC=Y
    $(info Add SW NVRAM)

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    SW_NVRAM=Y
    NVRAM=Y

    SW_NVRAM_DIR = $(STORAGE_DIR)/sw_nvram
    #@echo $(error SW_NVRAM_DIR=$(SW_NVRAM_DIR))
    INCDIR += -I$(SW_NVRAM_DIR)
    OPT += -DHAS_SW_NVRAM
    OPT += -DHAS_NVRAM

    SOURCES_C += $(SW_NVRAM_DIR)/sw_nvram.c

    ifeq ($(DIAG),Y)
        ifeq ($(SW_NVRAM_DIAG),Y)
            $(info Add SW NVRAM)
            OPT += -DHAS_SW_NVRAM_DIAG
            SOURCES_C += $(SW_NVRAM_DIR)/sw_nvram_diag.c
        endif
    endif


    ifeq ($(CLI),Y)
        ifeq ($(SW_NVRAM_COMMANDS),Y)
            $(info Add SW NVRAM Commands)
            OPT += -DHAS_SW_NVRAM_COMMANDS
            SOURCES_C += $(SW_NVRAM_DIR)/sw_nvram_commands.c
        endif
    endif

endif
