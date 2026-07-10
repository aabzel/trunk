ifneq ($(CONNECTIVITY_PRECONFIG_MK_INC),Y)
    CONNECTIVITY_PRECONFIG_MK_INC=Y

    CONNECTIVITY_DIR = $(WORKSPACE_LOC)/connectivity
    #@echo $(error CONNECTIVITY_DIR= $(CONNECTIVITY_DIR))

    ifeq ($(LOG),Y)
        #@echo $(error LOG=$(LOG))
        include $(CONNECTIVITY_DIR)/log/log_preconfig.mk
    endif

    ifeq ($(INTERFACES),Y)
        #@echo $(error INTERFACES=$(INTERFACES))
        include $(CONNECTIVITY_DIR)/interfaces/interfaces_preconfig.mk
    endif

    ifeq ($(PROTOCOLS),Y)  
        #@echo $(error PROTOCOLS=$(PROTOCOLS))
        include $(CONNECTIVITY_DIR)/protocols/protocols_preconfig.mk
    endif
endif