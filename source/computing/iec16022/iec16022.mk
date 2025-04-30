
ifneq ($(IEC16022_COM_MK_INC),Y)
    IEC16022_COM_MK_INC=Y

    IEC16022_COM_DIR = $(COMPUTING_DIR)/iec16022
    #@echo $(error IEC16022_DIR = $(IEC16022_DIR))
    INCDIR += -I$(IEC16022_COM_DIR)

    OPT += -DHAS_IEC16022

    SOURCES_C += $(IEC16022_COM_DIR)/iec16022_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(IEC16022_DIAG),Y)
            OPT += -DHAS_IEC16022_DIAG
            SOURCES_C += $(IEC16022_COM_DIR)/iec16022_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(IEC16022_COMMANDS),Y)
            #@echo $(error IEC16022_COMMANDS = $(IEC16022_COMMANDS))
            OPT += -DHAS_IEC16022_COMMANDS
            SOURCES_C += $(IEC16022_COM_DIR)/iec16022_commands.c
        endif
    endif
endif
