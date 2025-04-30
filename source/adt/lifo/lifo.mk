
$(info LIFO_MK_INC=$(LIFO_MK_INC))
ifneq ($(LIFO_MK_INC),Y)
    LIFO_MK_INC=Y

    LIFO_DIR = $(ADT_DIR)/lifo
    #@echo $(error LIFO_DIR= $(LIFO_DIR))
    OPT += -DHAS_LIFO
    INCDIR += -I$(LIFO_DIR)

    OPT += -DHAS_LIFO_INDEX
    SOURCES_C += $(LIFO_DIR)/lifo_index.c

    ifeq ($(LIFO_ARRAY),Y)
        OPT += -DHAS_LIFO_ARRAY
        SOURCES_C += $(LIFO_DIR)/lifo_array.c
        SOURCES_C += $(LIFO_DIR)/lifo_array_diag.c
    endif

endif