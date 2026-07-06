#Abstract data type

ifneq ($(THIRD_PARTY_ADT_MK),Y)
    THIRD_PARTY_ADT_MK=Y

    THIRD_PARTY_ADT_DIR = $(THIRD_PARTY_DIR)/adt
    # $(error THIRD_PARTY_ADT_DIR=$(THIRD_PARTY_ADT_DIR))
    MCAL_OPT += -DHAS_THIRD_PARTY_ADT
    MCAL_OPT += -DHAS_ADT_CLI

    INCDIR += -I$(THIRD_PARTY_ADT_DIR)

    ifeq ($(IQUEUE),Y)
        # $(error IQUEUE=$(IQUEUE))
        include $(THIRD_PARTY_ADT_DIR)/iqueue/iqueue.mk
    endif

endif