$(info GPS_MK_INC=$(GPS_MK_INC))

ifneq ($(GPS_MK_INC),Y)
    GPS_MK_INC=Y

    GPS_DIR = $(GNSS_DIR)/gps
    #@echo $(error GPS_DIR = $(GPS_DIR))
    INCDIR += -I$(GPS_DIR)

    MCAL_OPT += -DHAS_GPS

    SOURCES_C += $(GPS_DIR)/gps.c
    SOURCES_C += $(GPS_DIR)/gps_misc_1.c

    ifeq ($(DIAG),Y)
        ifeq ($(GPS_DIAG),Y)
            MCAL_OPT += -DHAS_GPS_DIAG
            SOURCES_C += $(GPS_DIR)/gps_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GPS_COMMANDS),Y)
            #@echo $(error GPS_COMMANDS = $(GPS_COMMANDS))
            MCAL_OPT += -DHAS_GPS_COMMANDS
            SOURCES_C += $(GPS_DIR)/gps_commands.c
        endif
    endif
endif
