$(info SWD_CUSTOM_MK_INC=$(SWD_CUSTOM_MK_INC) )
ifneq ($(SWD_CUSTOM_MK_INC),Y)
    SWD_CUSTOM_MK_INC=Y
   
    SWD_DIR = $(MCAL_STM32F4_DIR)/swd
    #@echo $(error SWD_DIR=$(SWD_DIR))
    
    INCDIR += -I$(SWD_DIR)

    SOURCES_C += $(SWD_DIR)/swd_mcal.c
    SOURCES_C += $(SWD_DIR)/writer_swd.c

    OPT += -DHAS_SWD_CUSTOM

    ifeq ($(DIAG),Y)
        OPT += -DHAS_SWD_CUSTOM_DIAG
        SOURCES_C += $(SWD_DIR)/swd_custom_diag.c
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(SWD_COMMANDS),Y)
            OPT += -DHAS_SWD_CUSTOM_COMMANDS
            SOURCES_C += $(SWD_DIR)/swd_custom_commands.c
        endif
    endif
    
endif