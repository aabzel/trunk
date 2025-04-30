
ifneq ($(FONT_COM_MK_INC),Y)
    FONT_COM_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    FONT_COM_DIR = $(STORAGE_DIR)/font
    #@echo $(error FONT_DIR = $(FONT_DIR))

    OPT += -DHAS_FONT
    FONT_SELECTED=N
    INCDIR += -I$(FONT_COM_DIR)
    SOURCES_C += $(FONT_COM_DIR)/fonts.c

    ifeq ($(DIAG),Y)
        ifeq ($(FONT_DIAG),Y)
            OPT += -DHAS_FONT_DIAG
            SOURCES_C += $(FONT_COM_DIR)/font_diag.c
        endif
    endif

    ifeq ($(FONT_12_X_6),Y)
        FONT_SELECTED=Y
        OPT += -DHAS_FONT_12_X_6
    endif

    ifeq ($(FONT_16_X_8),Y)
        FONT_SELECTED=Y
        OPT += -DHAS_FONT_16_X_8
    endif

    ifeq ($(FONT_24_X_12),Y)
        FONT_SELECTED=Y
        OPT += -DHAS_FONT_24_X_12
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(FONT_COMMANDS),Y)
            #@echo $(error FONT_COMMANDS = $(FONT_COMMANDS))
            OPT += -DHAS_FONT_COMMANDS
            SOURCES_C += $(FONT_COM_DIR)/font_commands.c
        endif
    endif
    
    ifeq ($(FONT_SELECTED),N)
        @echo $(error NoFontSelected)
    endif
endif
