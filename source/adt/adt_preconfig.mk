#Abstract data type

ifneq ($(ADT_PRECONFIG_MK),Y)
    ADT_PRECONFIG_MK=Y

    ADT_PRECONFIG_DIR = $(WORKSPACE_LOC)/adt

    ifeq ($(HISTOGRAM),Y)
        include $(ADT_PRECONFIG_DIR)/histogram/histogram_preconfig.mk
    endif

    ifeq ($(STRING),Y)
        include $(ADT_PRECONFIG_DIR)/string/string_preconfig.mk
    endif

    ifeq ($(ARRAY),Y)
        #$(error ARRAY=$(ARRAY))
        include $(ADT_PRECONFIG_DIR)/array/array_preconfig.mk
    endif

    ifeq ($(CIRCULAR_BUFFER),Y)
        include $(ADT_PRECONFIG_DIR)/circular_buffer/circular_buffer_preconfig.mk
    endif

    ifeq ($(FIFO),Y)
        include $(ADT_PRECONFIG_DIR)/fifo/fifo_preconfig.mk
    endif

    ifeq ($(HASHSET),Y)
        include $(ADT_PRECONFIG_DIR)/hashset/hashset_preconfig.mk
    endif

    ifeq ($(LIFO),Y)
        include $(ADT_PRECONFIG_DIR)/lifo/lifo_preconfig.mk
    endif

    ifeq ($(SET),Y)
        include $(ADT_PRECONFIG_DIR)/set/set_preconfig.mk
    endif
endif