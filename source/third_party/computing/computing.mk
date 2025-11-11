ifneq ($(TP_COMPUTING_MK_INC),Y)
    TP_COMPUTING_MK_INC=Y


    COMPUTING_DIRECTORY = $(THIRD_PARTY_DIR)/computing
    #@echo $(error COMPUTING_DIRECTORY= $(COMPUTING_DIRECTORY))

    OPT += -DHAS_THIRD_PARTY_COMPUTING
    OPT += -DCOMPUTING_IN_USE
    INCDIR += -I$(COMPUTING_DIRECTORY)
    
    SOURCES_THIRD_PARTY_C += $(COMPUTING_DIRECTORY)/computing_initialize.c
    SOURCES_THIRD_PARTY_C += $(COMPUTING_DIRECTORY)/computing_routines.c

    ifeq ($(DDS),Y)
        #@echo $(error DDS= $(DDS))
        include $(COMPUTING_DIRECTORY)/dds/dds.mk
    endif

    ifeq ($(VECTOR),Y)
        include $(COMPUTING_DIRECTORY)/vector/vector.mk
    endif

    ifeq ($(DSP),Y)
        include $(COMPUTING_DIRECTORY)/dsp/dsp.mk
    endif

    ifeq ($(PYRAMID_ACCEL_CALIBRATION),Y)
        include $(COMPUTING_DIRECTORY)/pyramid_accel_calibration/pyramid_accel_calibration.mk
    endif

    ifeq ($(CLI),Y)
        ifeq ($(COMPUTING_COMMANDS),Y)
            OPT += -DHAS_COMPUTING_CLI
            OPT += -DCOMPUTING_CLI_IN_USE
            SOURCES_THIRD_PARTY_C += $(COMPUTING_DIRECTORY)/computing_cli.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(COMPUTING_DIAG),Y)
            OPT += -DHAS_COMPUTING_DIAG
            OPT += -DCOMPUTING_DIAG_IN_USE
            #@echo $(error COMPUTING_DIAG=$(COMPUTING_DIAG))
            SOURCES_THIRD_PARTY_C += $(COMPUTING_DIRECTORY)/computing_diagnostic.c
        endif
    endif
endif