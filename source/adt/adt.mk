#Abstract data type

ifneq ($(ADT_MK),Y)
    ADT_MK=Y

    ADT_DIR = $(WORKSPACE_LOC)/adt
    # $(error ADT_DIR=$(ADT_DIR))
    # $(error ADT= $(ADT))
    MCAL_OPT += -DHAS_ADT

    INCDIR += -I$(ADT_DIR)

    #SOURCES_C += $(ADT_DIR)/adt_proc.c

    ifeq ($(HASH_TABLE_S8),Y)
        # $(error HASH_TABLE_S8=$(HASH_TABLE__S8))
        include $(ADT_DIR)/hash_table_s8/hash_table_s8.mk
    endif
    
    ifeq ($(HASH_TABLE),Y)
        # $(error HASH_TABLE=$(HASH_TABLE))
        # include $(ADT_DIR)/hash_table/hash_table.mk
    endif

    ifeq ($(HISTOGRAM),Y)
        # $(error HISTOGRAM=$(HISTOGRAM))
        include $(ADT_DIR)/histogram/histogram.mk
    endif

    ifeq ($(ADT_COMMANDS),Y)
        # $(error ADT_COMMANDS= $(ADT_COMMANDS))
        MCAL_OPT += -DHAS_ADT_COMMANDS
    endif

    ifeq ($(ARRAY),Y)
        # $(error ARRAY=$(ARRAY))
        include $(ADT_DIR)/array/array.mk
    endif

    ifeq ($(BIN_HEAP),Y)
        include $(ADT_DIR)/bin_heap/bin_heap.mk
    endif

    ifeq ($(CIRCULAR_BUFFER),Y)
        include $(ADT_DIR)/circular_buffer/circular_buffer.mk
    endif

    ifeq ($(FIFO),Y)
        # $(error FIFO=$(FIFO))
        include $(ADT_DIR)/fifo/fifo.mk
    endif

    ifeq ($(BIT_FIFO),Y)
        # $(error BIT_FIFO=$(BIT_FIFO))
        include $(ADT_DIR)/bit_fifo/bit_fifo.mk
    endif
    
    ifeq ($(MAX_HEAP),Y)
        include $(ADT_DIR)/max_heap/max_heap.mk
    endif

    ifeq ($(MIN_HEAP),Y)
        include $(ADT_DIR)/min_heap/min_heap.mk
    endif

    ifeq ($(HASHSET),Y)
        include $(ADT_DIR)/hashset/hashset.mk
    endif

    ifeq ($(LIFO),Y)
        include $(ADT_DIR)/lifo/lifo.mk
    endif

    ifeq ($(SET),Y)
        # $(error SET=$(SET))
        #include $(ADT_DIR)/set/set.mk
    endif

    ifeq ($(STRING),Y)
        # $(error STRING=$(STRING))
        include $(ADT_DIR)/string/string.mk
    endif
endif