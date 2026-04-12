
ifneq ($(NMEA_MK),Y)
    NMEA_MK=Y

    $(info Build  NMEA )

    NMEA_DIR = $(PROTOCOLS_DIR)/nmea
    
    #@ echo $(error NMEA_DIR = $(NMEA_DIR)) 

    MCAL_OPT += -DHAS_NMEA
    MCAL_OPT += -DHAS_NMEA_PROC

    MCAL_OPT += -DHAS_NMEA_GGA
    MCAL_OPT += -DHAS_NMEA_GLL
    MCAL_OPT += -DHAS_NMEA_GSA
    MCAL_OPT += -DHAS_NMEA_GSV
    MCAL_OPT += -DHAS_NMEA_PBUX
    MCAL_OPT += -DHAS_NMEA_RMC
    MCAL_OPT += -DHAS_NMEA_VTG
    MCAL_OPT += -DHAS_NMEA_ZDA

    INCDIR += -I$(NMEA_DIR)

    SOURCES_C +=$(NMEA_DIR)/nmea_protocol.c
    SOURCES_C +=$(NMEA_DIR)/nmea_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(NMEA_DIAG),Y)
            MCAL_OPT += -DHAS_NMEA_DIAG
            SOURCES_C +=$(NMEA_DIR)/nmea_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NMEA_COMMANDS),Y)
            MCAL_OPT += -DHAS_NMEA_COMMANDS
            SOURCES_C +=$(NMEA_DIR)/nmea_commands.c
        endif
    endif
endif



