ifneq ($(UBLOX_NEO_6M_MK_INC),Y)
    UBLOX_NEO_6M_MK_INC=Y

    UBLOX_NEO_6M_DIR = $(ASICS_DIR)/ublox_neo_6m
    #@echo $(error UBLOX_NEO_6M_DIR=$(UBLOX_NEO_6M_DIR))

    INCDIR += -I$(UBLOX_NEO_6M_DIR)

    MCAL_OPT += -DHAS_UBLOX_NEO_6M
    MCAL_OPT += -DHAS_UBLOX_NEO_6M_PROC

    SOURCES_C += $(UBLOX_NEO_6M_DIR)/ublox_neo_6m.c

    ifeq ($(DIAG),Y)
        ifeq ($(UBLOX_NEO_6M_DIAG),Y)
            MCAL_OPT += -DHAS_UBLOX_NEO_6M_DIAG
            SOURCES_C += $(UBLOX_NEO_6M_DIR)/ublox_neo_6m_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UBLOX_NEO_6M_COMMANDS),Y)
            MCAL_OPT += -DHAS_UBLOX_NEO_6M_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(UBLOX_NEO_6M_DIR)/ublox_neo_6m_commands.c
        endif
    endif
endif
