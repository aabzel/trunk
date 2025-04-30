$(info MICROCONTROLLER_PRECONFIG_INC= $(MICROCONTROLLER_PRECONFIG_INC))
ifneq ($(MICROCONTROLLER_PRECONFIG_INC),Y)
    MICROCONTROLLER_PRECONFIG_INC=Y

    MICROCONTROLLER_DIR = $(WORKSPACE_LOC)/microcontroller
    #@echo $(error MICROCONTROLLER_DIR=$(MICROCONTROLLER_DIR))

    MICROCONTROLLER=Y


    ifeq ($(AT32F413RC),Y)
        #@echo $(error AT32F413RC=$(AT32F413RC))
        include $(MICROCONTROLLER_DIR)/at32f413rc/at32f413rc_preconfig.mk
    endif

    ifeq ($(AT32F435ZM),Y)
        #@echo $(error AT32F435ZM=$(AT32F435ZM))
        include $(MICROCONTROLLER_DIR)/at32f435zm/at32f435zm_preconfig.mk
    endif

    ifeq ($(AT32F437ZM),Y)
        #@echo $(error AT32F437ZM=$(AT32F437ZM))
        include $(MICROCONTROLLER_DIR)/at32f437zm/at32f437zm_preconfig.mk
    endif

    ifeq ($(YTM32B1ME05G0MLQ),Y)
        #@echo $(error YTM32B1ME05G0MLQ=$(YTM32B1ME05G0MLQ))
        include $(MICROCONTROLLER_DIR)/ytm32b1me05g0mlq/ytm32b1me05g0mlq_preconfig.mk
    endif

    ifeq ($(AT32F4XXXX),Y)
        #@echo $(error AT32F4XXXX=$(AT32F4XXXX))
        include $(MICROCONTROLLER_DIR)/at32f4xxxx/at32f4xxxx_preconfig.mk
    endif
  
endif
