$(info CORE_GENERAL_PRECONFIG_MK_INC=$(CORE_GENERAL_PRECONFIG_MK_INC) )

ifneq ($(CORE_GENERAL_PRECONFIG_MK_INC),Y)
    CORE_GENERAL_PRECONFIG_MK_INC=Y
    CORE=Y
    MICROCONTROLLER=Y
    CORE_DIR = $(WORKSPACE_LOC)/core
    ifeq ($(CORTEX_M0),Y)
        include $(CORE_DIR)/cortex_m0/cortex_m0_preconfig.mk
    endif

    ifeq ($(CORTEX_M3),Y)
        include $(CORE_DIR)/cortex_m3/cortex_m3_preconfig.mk
    endif

    ifeq ($(CORTEX_M4),Y)
        include $(CORE_DIR)/cortex_m4/cortex_m4_preconfig.mk
    endif

    ifeq ($(CORTEX_M7),Y)
        include $(CORE_DIR)/cortex_m7/cortex_m7_preconfig.mk
    endif

    ifeq ($(CORTEX_M33),Y)
        include $(CORE_DIR)/cortex_m33/cortex_m33_preconfig.mk
    endif




endif