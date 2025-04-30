
$(info FIFO_MK_INC=$(FIFO_MK_INC))
ifneq ($(FIFO_MK_INC),Y)
    FIFO_MK_INC=Y

    FIFO_DIR = $(ADT_DIR)/fifo
    #@echo $(error FIFO_DIR= $(FIFO_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    OPT += -DHAS_FIFO
    INCDIR += -I$(FIFO_DIR)
    
    ifeq ($(FIFO_EXT),Y)
        OPT += -DHAS_FIFO_EXT
    endif
    
    ifeq ($(FIFO_INDEX),Y)
        OPT += -DHAS_FIFO_INDEX
        SOURCES_C += $(FIFO_DIR)/fifo_index.c
    endif
    
    ifeq ($(FIFO_ARRAY),Y)
        OPT += -DHAS_FIFO_ARRAY
        SOURCES_C += $(FIFO_DIR)/fifo_array.c
    endif
    
    ifeq ($(FIFO_CHAR),Y)
        #@echo $(error FIFO_CHAR= $(FIFO_CHAR))
        OPT += -DHAS_FIFO_CHAR
        SOURCES_C += $(FIFO_DIR)/fifo_char.c
    endif
    
endif