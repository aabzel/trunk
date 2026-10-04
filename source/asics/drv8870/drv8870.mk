ifneq ($(DRV8870_MK_INC),Y)
    DRV8870_MK_INC=Y

    DRV8870_DIR = $(ASICS_DIR)/drv8870
    # $(error DRV8870_DIR=$(DRV8870_DIR))

    INCDIR += -I$(DRV8870_DIR)

    MCAL_OPT += -DHAS_DRV8870

    MCAL_OPT += -DHAS_DRV8870_PROC

    SOURCES_C += $(DRV8870_DIR)/drv8870.c

    ifeq ($(DRV8870_1),Y)
        MCAL_OPT += -DHAS_DRV8870_1
    endif

    ifeq ($(DRV8870_2),Y)
        MCAL_OPT += -DHAS_DRV8870_2
    endif


    ifeq ($(DRV8870_INTERRUPT),Y)
        MCAL_OPT += -DHAS_DRV8870_INTERRUPT
        SOURCES_C += $(DRV8870_DIR)/drv8870_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DRV8870_DIAG),Y)
            MCAL_OPT += -DHAS_DRV8870_DIAG
            SOURCES_C += $(DRV8870_DIR)/drv8870_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DRV8870_COMMANDS),Y)
            MCAL_OPT += -DHAS_DRV8870_COMMANDS
            SOURCES_C += $(DRV8870_DIR)/drv8870_commands.c
        endif
    endif
endif
