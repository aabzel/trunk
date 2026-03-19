$(info TP_COMPUTING_DDS_MK_INC=$(TP_COMPUTING_DDS_MK_INC))
ifneq ($(TP_COMPUTING_DDS_MK_INC),Y)
    TP_COMPUTING_DDS_MK_INC=Y
    $(info Add DDS)

    DDS_DIRECTORY = $(COMPUTING_DIRECTORY)/dds
    #@echo $(error DDS_DIRECTORY=$(DDS_DIRECTORY))
                
    INCDIR += -I$(DDS_DIRECTORY)
    
    OPT += -DDDS_IN_USE
    OPT += -DDDS_PROC_IN_USE
    DDS=Y

    ifeq ($(DDS_STATIC_SAMPLES),Y)
        OPT += -DDDS_STATIC_SAMPLES_IN_USE
    endif

    ifeq ($(REAL_SAMPLE_ARRAY),Y)
        OPT += -DDDS_REAL_SAMPLE_IN_USE
    endif

    SOURCES_THIRD_PARTY_C += $(DDS_DIRECTORY)/dds.c
    SOURCES_THIRD_PARTY_C += $(DDS_DIRECTORY)/dds_configuration.c

    ifeq ($(DIAG),Y)
        ifeq ($(DDS_DIAG),Y)
            #@echo $(error DDS_DIAG=$(DDS_DIAG))
            $(info Add DDS DIAG)
            OPT += -DDDS_IN_USE_DIAG
            SOURCES_THIRD_PARTY_C += $(DDS_DIRECTORY)/dds_diagnostic.c
        endif
    endif

    #@echo $(error DDS_DIRECTORY=$(DDS_DIRECTORY))

    ifeq ($(CLI),Y)
        ifeq ($(DDS_COMMANDS),Y)
            $(info Add DDS CLI)
            OPT += -DHAS_DDS_CLI
            OPT += -DDDS_CLI_IN_USE
            SOURCES_THIRD_PARTY_C += $(DDS_DIRECTORY)/dds_cli.c
        endif
    endif

endif
