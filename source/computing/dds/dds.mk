$(info COMPUTING_DDS_MK_INC=$(COMPUTING_DDS_MK_INC))
ifneq ($(COMPUTING_DDS_MK_INC),Y)
    COMPUTING_DDS_MK_INC=Y
    $(info Add DDS)

    DDS_DIR = $(COMPUTING_DIR)/dds
    INCDIR += -I$(DDS_DIR)
    MCAL_OPT += -DHAS_DDS

    ifeq ($(DDS_PROC),Y)
        MCAL_OPT += -DHAS_DDS_PROC
    endif

    ifeq ($(DDS_STATIC_SAMPLES),Y)
        MCAL_OPT += -DHAS_DDS_STATIC_SAMPLES
    endif

    ifeq ($(DYNAMIC_SAMPLES),Y)
        MCAL_OPT += -DHAS_DYNAMIC_SAMPLES
    endif

    ifeq ($(REAL_SAMPLE_ARRAY),Y)
        MCAL_OPT += -DHAS_REAL_SAMPLE_ARRAY
    endif

    #SOURCES_C += $(DDS_DIR)/dds_config.c
    SOURCES_C += $(DDS_DIR)/dds_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(DDS_DIAG),Y)
            #  $(error DDS_DIAG=$(DDS_DIAG))
            $(info Add DDS)
            MCAL_OPT += -DHAS_DDS_DIAG
            SOURCES_DIAG_C += $(DDS_DIR)/dds_diag.c
        endif
    endif


    ifeq ($(CLI),Y)
        ifeq ($(DDS_COMMANDS),Y)
            $(info Add DDS Commands)
            MCAL_OPT += -DHAS_DDS_COMMANDS
            SOURCES_C += $(DDS_DIR)/dds_commands.c
        endif
    endif

endif
