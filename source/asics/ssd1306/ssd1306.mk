ifneq ($(SSD1306_MK_INC),Y)
    SSD1306_MK_INC=Y

    SSD1306_DIR = $(ASICS_DIR)/ssd1306
    #@echo $(error SSD1306_DIR=$(SSD1306_DIR))

    INCDIR += -I$(SSD1306_DIR)

    OPT += -DHAS_SSD1306
    OPT += -DHAS_SSD1306_PROC

    SOURCES_C += $(SSD1306_DIR)/ssd1306_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(SSD1306_DIAG),Y)
            OPT += -DHAS_SSD1306_DIAG
            SOURCES_C += $(SSD1306_DIR)/ssd1306_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SSD1306_COMMANDS),Y)
            OPT += -DHAS_SSD1306_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(SSD1306_DIR)/ssd1306_commands.c
        endif
    endif
endif
