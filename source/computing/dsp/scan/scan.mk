
$(info SCAN_MK_INC=$(SCAN_MK_INC))

ifneq ($(SCAN_MK_INC),Y)
    SCAN_MK_INC=Y

    SCAN_DIR = $(DSP_DIR)/scan
    # $(error SCAN_DIR=$(SCAN_DIR))

    INCDIR += -I$(SCAN_DIR)
    SOURCES_C += $(SCAN_DIR)/scan.c
    #SOURCES_H += $(SCAN_DIR)/scan.h

    SCAN=Y
    OPT += -DHAS_SCAN

    ifeq ($(DIAG),Y)
        #@echo $(error SCAN_DIAG=$(SCAN_DIAG))
        OPT += -DHAS_SCAN_DIAG
        SOURCES_C += $(SCAN_DIR)/scan_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SCAN_COMMANDS),Y)
            OPT += -DHAS_SCAN_COMMANDS
            SOURCES_C += $(SCAN_DIR)/scan_commands.c
        endif
    endif
endif