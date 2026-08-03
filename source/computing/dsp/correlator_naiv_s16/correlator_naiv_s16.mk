$(info CORRELATOR_NAIV_S16_MK_INC=$(CORRELATOR_NAIV_S16_MK_INC) )

ifneq ($(CORRELATOR_NAIV_S16_MK_INC),Y)
    CORRELATOR_NAIV_S16_MK_INC=Y

    CORRELATOR_NAIV_S16_DIR = $(DSP_DIR)/correlator_naiv_s16
    # $(error CORRELATOR_NAIV_S16_DIR=[$(CORRELATOR_NAIV_S16_DIR)])
    INCDIR += -I$(CORRELATOR_NAIV_S16_DIR)

    MCAL_OPT += -DHAS_CORRELATOR_NAIV_S16

    SOURCES_C += $(CORRELATOR_NAIV_S16_DIR)/correlator_naiv_s16.c

    ifeq ($(DIAG),Y)
        ifeq ($(CORRELATOR_NAIV_S16_DIAG),Y)
            MCAL_OPT += -DHAS_CORRELATOR_NAIV_S16_DIAG
            SOURCES_C += $(CORRELATOR_NAIV_S16_DIR)/correlator_naiv_s16_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CORRELATOR_NAIV_S16_COMMANDS),Y)
            # $(error CORRELATOR_NAIV_S16_COMMANDS=[$(CORRELATOR_NAIV_S16_COMMANDS)])
            MCAL_OPT += -DHAS_CORRELATOR_NAIV_S16_COMMANDS
            SOURCES_C += $(CORRELATOR_NAIV_S16_DIR)/correlator_naiv_s16_commands.c
        endif
    endif
endif






