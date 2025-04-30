
ifneq ($(NMEA_MK),Y)
    NMEA_MK=Y

    $(info Build  NMEA )

    NMEA_DIR = $(PROTOCOLS_DIR)/nmea
    
    #@ echo $(error NMEA_DIR = $(NMEA_DIR)) 

    OPT += -DHAS_NMEA
    OPT += -DHAS_NMEA_PROC

    OPT += -DHAS_NMEA_GGA
    OPT += -DHAS_NMEA_GLL
    OPT += -DHAS_NMEA_GSA
    OPT += -DHAS_NMEA_GSV
    OPT += -DHAS_NMEA_PBUX
    OPT += -DHAS_NMEA_RMC
    OPT += -DHAS_NMEA_VTG
    OPT += -DHAS_NMEA_ZDA

    INCDIR += -I$(NMEA_DIR)

    SOURCES_C +=$(NMEA_DIR)/nmea_protocol.c
    SOURCES_C +=$(NMEA_DIR)/nmea_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(NMEA_DIAG),Y)
            OPT += -DHAS_NMEA_DIAG
            SOURCES_C +=$(NMEA_DIR)/nmea_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NMEA_COMMANDS),Y)
            OPT += -DHAS_NMEA_COMMANDS
            SOURCES_C +=$(NMEA_DIR)/nmea_commands.c
        endif
    endif
endif



