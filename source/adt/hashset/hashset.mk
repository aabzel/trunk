
$(info HASHSET_MK_INC=$(HASHSET_MK_INC))

ifneq ($(HASHSET_MK_INC),Y)
    HASHSET_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    HASHSET_DIR = $(ADT_DIR)/hashset
    #@echo $(error HASHSET_DIR= $(HASHSET_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    OPT += -DHAS_HASHSET
    INCDIR += -I$(HASHSET_DIR)
    
    SOURCES_C += $(HASHSET_DIR)/hashset.c
    SOURCES_C += $(HASHSET_DIR)/hashset_config.c

endif