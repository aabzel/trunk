$(info CORTEX_M33_MK_INC=$(CORTEX_M33_MK_INC) )
ifneq ($(CORTEX_M33_MK_INC),Y)
    CORTEX_M33_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    CORTEX_M33_DIR = $(CORE_DIR)/cortex_m33
    INCDIR += -I$(CORTEX_M33_DIR)
    #@echo $(error CORTEX_M33=$(CORTEX_M33))
    MCU=Y
    OPT += -DHAS_ARM
    OPT += -DHAS_CORTEX_M33
    
    ifeq ($(CORE_NET), Y)
        FPU +=
        #CPU += -mcpu=cortex-m33
        CPU += -march=armv8-m.main
    endif

    ifeq ($(CORE_APP), Y)
       #FPU += -mfpu=fpv4-sp-d16
        FPU += -mfpu=fpv5-sp-d16
        CPU += -mcpu=cortex-m33
    endif

    SOURCES_C += $(CORTEX_M33_DIR)/cortex_m33_driver.c

    ifeq ($(DIAG),Y)
        ifeq ($(DIAG_CORE),Y)
            SOURCES_C += $(CORTEX_M33_DIR)/cortex_m33_diag.c
        endif
    endif

    include $(CORTEX_M33_DIR)/nvic/nvic.mk

    ifeq ($(SYSTICK),Y)
        #@echo $(error SYSTICK=$(SYSTICK))
        include $(CORTEX_M33_DIR)/systick/systick.mk
    endif
endif