$(info COMMON_PRECONFIG_INC=  $(COMMON_PRECONFIG_INC) )
ifneq ($(COMMON_PRECONFIG_INC),Y)
    COMMON_PRECONFIG_INC=Y

    COMMON_DIR = $(WORKSPACE_LOC)/common
    INCDIR += -I$(COMMON_DIR)

    include $(COMMON_DIR)/code_generator/code_generator.mk
    
    
    ifeq ($(SW_COMPONENT),Y)
        include $(COMMON_DIR)/sw_component/sw_component_preconfig.mk
    endif

endif
