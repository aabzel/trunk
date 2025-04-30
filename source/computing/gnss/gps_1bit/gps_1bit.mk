$(info GPS_MK_INC=$(GPS_MK_INC))

ifneq ($(GPS_1BIT_MK_INC),Y)
    GPS_MK_INC=Y

    GPS_1BIT_DIR = $(GNSS_DIR)/gps_1bit
    #@echo $(error GPS_1BIT_DIR = $(GPS_1BIT_DIR))
    INCDIR += -I$(GPS_1BIT_DIR)

    OPT += -DHAS_GPS_1BIT

    SOURCES_C += $(GPS_1BIT_DIR)/gps_1bit.c
    SOURCES_C += $(GPS_1BIT_DIR)/gps_misc.c

    ifeq ($(DIAG),Y)
        ifeq ($(GPS_1BIT_DIAG),Y)
            OPT += -DHAS_GPS_1BIT_DIAG
            SOURCES_C += $(GPS_1BIT_DIR)/gps_1bit_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GPS_1BIT_COMMANDS),Y)
            #@echo $(error GPS_1BIT_COMMANDS = $(GPS_1BIT_COMMANDS))
            OPT += -DHAS_GPS_1BIT_COMMANDS
            SOURCES_C += $(GPS_1BIT_DIR)/gps_1bit_commands.c
        endif
    endif
endif
