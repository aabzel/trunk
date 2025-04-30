#Abstract data type

ifneq ($(ADT_MK),Y)
    ADT_MK=Y

    ADT_DIR = $(WORKSPACE_LOC)/adt
    #@echo $(error ADT_DIR=$(ADT_DIR))
    #@echo $(error ADT= $(ADT))
    OPT += -DHAS_ADT

    INCDIR += -I$(ADT_DIR)

    #SOURCES_C += $(ADT_DIR)/adt_proc.c

    ifeq ($(HISTOGRAM),Y)
        #@echo $(error HISTOGRAM=$(HISTOGRAM))
        include $(ADT_DIR)/histogram/histogram.mk
    endif

    ifeq ($(ADT_COMMANDS),Y)
        #@echo $(error ADT_COMMANDS= $(ADT_COMMANDS))
        OPT += -DHAS_ADT_COMMANDS
    endif

    ifeq ($(ARRAY),Y)
        #@echo $(error ARRAY=$(ARRAY))
        include $(ADT_DIR)/array/array.mk
    endif

    ifeq ($(CIRCULAR_BUFFER),Y)
        include $(ADT_DIR)/circular_buffer/circular_buffer.mk
    endif

    ifeq ($(FIFO),Y)
        #@echo $(error FIFO=$(FIFO))
        include $(ADT_DIR)/fifo/fifo.mk
    endif

    ifeq ($(HASHSET),Y)
        include $(ADT_DIR)/hashset/hashset.mk
    endif

    ifeq ($(LIFO),Y)
        include $(ADT_DIR)/lifo/lifo.mk
    endif

    ifeq ($(SET),Y)
        #@echo $(error SET=$(SET))
        #include $(ADT_DIR)/set/set.mk
    endif

    ifeq ($(STRING),Y)
        #@echo $(error STRING=$(STRING))
        include $(ADT_DIR)/string/string.mk
    endif
endif