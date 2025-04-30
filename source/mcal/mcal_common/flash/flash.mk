
$(info FLASH_MCAL_MK_INC=$(FLASH_MCAL_MK_INC))
ifneq ($(FLASH_MCAL_MK_INC),Y)
    FLASH_MCAL_MK_INC=Y

    FLASH_MCAL_DIR = $(MCAL_COMMON_DIR)/flash
    #@echo $(error FLASH_MCAL_DIR=$(FLASH_MCAL_DIR))

    INCDIR += -I$(FLASH_MCAL_DIR)
    OPT += -DHAS_FLASH

    SOURCES_C += $(FLASH_MCAL_DIR)/flash_common.c

    ifeq ($(CRC16),N)
        @echo $(warning Add CRC16)
    endif

    #CRC16=Y
    #OPT += -DHAS_CRC16

    ifeq ($(FLASH_EX),Y)
        OPT += -DHAS_FLASH_EX
    endif

    ifeq ($(FLASH_WRITE),Y)
        #@echo $(error FLASH_WRITE=$(FLASH_WRITE))
        OPT += -DHAS_FLASH_WRITE
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(FLASH_DIAG),Y)
            OPT += -DHAS_FLASH_DIAG
            SOURCES_C += $(FLASH_MCAL_DIR)/flash_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(FLASH_COMMANDS),Y)
            #@echo $(error FLASH_COMMANDS=$(FLASH_COMMANDS))
            OPT += -DHAS_FLASH_COMMANDS
            SOURCES_C += $(FLASH_MCAL_DIR)/flash_commands.c
        endif
    endif
endif


