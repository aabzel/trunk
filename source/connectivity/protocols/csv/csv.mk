
$(info CSV_MK_INC=$(CSV_MK_INC))

ifneq ($(CSV_MK_INC),Y)
    CSV_MK_INC=Y

    CSV_DIR = $(PROTOCOLS_DIR)/csv
    #@echo $(error CSV_DIR= $(CSV_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    OPT += -DHAS_CSV
    INCDIR += -I$(CSV_DIR)

    SOURCES_C += $(CSV_DIR)/csv.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_CSV_DIAG
        SOURCES_C += $(CSV_DIR)/csv_diag.c
    endif
endif