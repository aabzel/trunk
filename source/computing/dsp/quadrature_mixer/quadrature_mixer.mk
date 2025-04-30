$(info QUADRATURE_MIXER_MK_INC=$(QUADRATURE_MIXER_MK_INC) )

ifneq ($(QUADRATURE_MIXER_MK_INC),Y)
    QUADRATURE_MIXER_MK_INC=Y

    QUADRATURE_MIXER_DIR = $(DSP_DIR)/quadrature_mixer
    #@echo $(error QUADRATURE_MIXER_DIR=[$(QUADRATURE_MIXER_DIR)])
    INCDIR += -I$(QUADRATURE_MIXER_DIR)

    OPT += -DHAS_QUADRATURE_MIXER

    SOURCES_C += $(QUADRATURE_MIXER_DIR)/quadrature_mixer.c

    ifeq ($(DIAG),Y)
        ifeq ($(QUADRATURE_MIXER_DIAG),Y)
            OPT += -DHAS_QUADRATURE_MIXER_DIAG
            SOURCES_C += $(QUADRATURE_MIXER_DIR)/quadrature_mixer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(QUADRATURE_MIXER_COMMANDS),Y)
            #@echo $(error QUADRATURE_MIXER_COMMANDS=[$(QUADRATURE_MIXER_COMMANDS)])
            OPT += -DHAS_QUADRATURE_MIXER_COMMANDS
            SOURCES_C += $(QUADRATURE_MIXER_DIR)/quadrature_mixer_commands.c
        endif
    endif
endif






