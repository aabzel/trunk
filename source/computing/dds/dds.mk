$(info COMPUTING_DDS_MK_INC=$(COMPUTING_DDS_MK_INC))
ifneq ($(COMPUTING_DDS_MK_INC),Y)
    COMPUTING_DDS_MK_INC=Y
    $(info Add DDS)

    DDS=Y
    DDS_DIR = $(COMPUTING_DIR)/dds
    INCDIR += -I$(DDS_DIR)
    OPT += -DHAS_DDS
    OPT += -DHAS_DDS_PROC

    ifeq ($(DDS_STATIC_SAMPLES),Y)
        OPT += -DHAS_DDS_STATIC_SAMPLES
    endif

    ifeq ($(DYNAMIC_SAMPLES),Y)
        OPT += -DHAS_DYNAMIC_SAMPLES
    endif

    ifeq ($(REAL_SAMPLE_ARRAY),Y)
        OPT += -DHAS_REAL_SAMPLE_ARRAY
    endif

    SOURCES_C += $(DDS_DIR)/dds_config.c
    SOURCES_C += $(DDS_DIR)/dds_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(DDS_DIAG),Y)
            #@echo $(error DDS_DIAG=$(DDS_DIAG))
            $(info Add DDS)
            OPT += -DHAS_DDS_DIAG
            SOURCES_C += $(DDS_DIR)/dds_diag.c
        endif
    endif

    #@echo $(error DDS_DIR=$(DDS_DIR))

    ifeq ($(CLI),Y)
        ifeq ($(DDS_COMMANDS),Y)
            $(info Add DDS Commands)
            OPT += -DHAS_DDS_COMMANDS
            SOURCES_C += $(DDS_DIR)/dds_commands.c
        endif
    endif

endif
