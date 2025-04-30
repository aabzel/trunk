$(info GNSS_MK_INC=$(GNSS_MK_INC))

ifneq ($(GNSS_MK_INC),Y)
    GNSS_MK_INC=Y

    GNSS_DIR = $(COMPUTING_DIR)/gnss
    #@echo $(error GNSS_DIR = $(GNSS_DIR))

    OPT += -DHAS_GNSS

    INCDIR += -I$(GNSS_DIR)

    SOURCES_C += $(GNSS_DIR)/gnss_drv.c
    SOURCES_C += $(GNSS_DIR)/gnss_utils.c

    ifeq ($(GPS),Y)
        include $(GNSS_DIR)/gps/gps.mk
    endif

    ifeq ($(GPS_1BIT),Y)
        #@echo $(error GPS_1BIT=$(GPS_1BIT))
        include $(GNSS_DIR)/gps_1bit/gps_1bit.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(GNSS_DIAG),Y)
            OPT += -DHAS_GNSS_DIAG
            SOURCES_C += $(GNSS_DIR)/gnss_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GNSS_COMMANDS),Y)
            #@echo $(error GNSS_COMMANDS = $(GNSS_COMMANDS))
            OPT += -DHAS_GNSS_COMMANDS
            SOURCES_C += $(GNSS_DIR)/gnss_commands.c
        endif
    endif
endif
