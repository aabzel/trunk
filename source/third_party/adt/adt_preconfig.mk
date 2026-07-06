#Abstract data type

ifneq ($(THIRD_PARTY_ADT_PRECONFIG_MK),Y)
    THIRD_PARTY_ADT_PRECONFIG_MK=Y

    THIRD_PARTY_ADT_PRECONFIG_DIR = $(THIRD_PARTY_DIR)/adt

    ifeq ($(IQUEUE),Y)
        include $(THIRD_PARTY_ADT_PRECONFIG_DIR)/iqueue/iqueue_preconfig.mk
    endif
endif