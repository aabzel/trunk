$(info MULTICORE_COMMON_MCAL_MK_INC=$(MULTICORE_COMMON_MCAL_MK_INC) )

ifneq ($(MULTICORE_COMMON_MCAL_MK_INC),Y)
    MULTICORE_COMMON_MCAL_MK_INC=Y

    MULTICORE_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/multicore
    #@echo $(error MULTICORE_COMMON_MCAL_DIR=$(MULTICORE_COMMON_MCAL_DIR))

    INCDIR += -I$(MULTICORE_COMMON_MCAL_DIR)
    MCAL_OPT += -DHAS_MULTICORE

    SOURCES_C += $(MULTICORE_COMMON_MCAL_DIR)/multicore_general.c

    ifeq ($(MULTICORE_ISR),Y)
        MCAL_OPT += -DHAS_MULTICORE_ISR
        SOURCES_C += $(MULTICORE_COMMON_MCAL_DIR)/multicore_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MULTICORE_DIAG),Y)
            MCAL_OPT += -DHAS_MULTICORE_DIAG
            SOURCES_C += $(MULTICORE_COMMON_MCAL_DIR)/multicore_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MULTICORE_COMMANDS),Y)
            MCAL_OPT += -DHAS_MULTICORE_COMMANDS
            SOURCES_C += $(MULTICORE_COMMON_MCAL_DIR)/multicore_commands.c
        endif
    endif    
endif