ifneq ($(LOG_PRECONFIG_MK_INC),Y)
    LOG_PRECONFIG_MK_INC=Y
    #@echo $(error LOG_DIR=$(LOG_DIR))
    #INTERFACES->LOG
endif