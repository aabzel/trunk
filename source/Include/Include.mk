ifneq ($(INCLUDE_MK_INC),Y)
    INCLUDE_MK_INC=Y

    INCLUDE_DIR = $(WORKSPACE_LOC)Include
    #@echo $(error INCLUDE_DIR= $(INCLUDE_DIR))
    INCDIR += -I$(INCLUDE_DIR)
endif
