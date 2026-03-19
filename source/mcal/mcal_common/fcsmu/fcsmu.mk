$(info FCSMU_COMMON_MCAL_MK_INC=$(FCSMU_COMMON_MCAL_MK_INC) )

ifneq ($(FCSMU_COMMON_MCAL_MK_INC),Y)
    FCSMU_COMMON_MCAL_MK_INC=Y

    FCSMU_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/fcsmu
    #@echo $(error FCSMU_COMMON_MCAL_DIR=$(FCSMU_COMMON_MCAL_DIR))

    INCDIR += -I$(FCSMU_COMMON_MCAL_DIR)
    MCAL_OPT += -DHAS_FCSMU
    MCAL_OPT += -DHAS_FCSMU_PROC

    SOURCES_C += $(FCSMU_COMMON_MCAL_DIR)/fcsmu_general.c

    ifeq ($(FCSMU_INTERRUPT),Y)
        MCAL_OPT += -DHAS_FCSMU_INTERRUPT
        SOURCES_C += $(FCSMU_COMMON_MCAL_DIR)/fcsmu_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(FCSMU_DIAG),Y)
            MCAL_OPT += -DHAS_FCSMU_DIAG
            SOURCES_C += $(FCSMU_COMMON_MCAL_DIR)/fcsmu_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FCSMU_COMMANDS),Y)
            MCAL_OPT += -DHAS_FCSMU_COMMANDS
            SOURCES_C += $(FCSMU_COMMON_MCAL_DIR)/fcsmu_commands.c
        endif
    endif    
endif