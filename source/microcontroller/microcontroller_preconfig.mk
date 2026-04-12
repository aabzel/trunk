$(info MICROCONTROLLER_PRECONFIG_INC= $(MICROCONTROLLER_PRECONFIG_INC))
ifneq ($(MICROCONTROLLER_PRECONFIG_INC),Y)
    MICROCONTROLLER_PRECONFIG_INC=Y

    MICROCONTROLLER_DIR = $(WORKSPACE_LOC)/microcontroller
    # $(error MICROCONTROLLER_DIR=$(MICROCONTROLLER_DIR))

    MICROCONTROLLER=Y

    ifeq ($(AT32F413RC),Y)
        # $(error AT32F413RC=$(AT32F413RC))
        include $(MICROCONTROLLER_DIR)/at32f413rc/at32f413rc_preconfig.mk
    endif

    ifeq ($(AT32F435ZM),Y)
        # $(error AT32F435ZM=$(AT32F435ZM))
        include $(MICROCONTROLLER_DIR)/at32f435zm/at32f435zm_preconfig.mk
    endif

    ifeq ($(STM32F407ZG),Y)
        # $(error AT32F437ZM=$(AT32F437ZM))
        include $(MICROCONTROLLER_DIR)/stm32f407zg/stm32f407zg_preconfig.mk
    endif

    ifeq ($(STM32F407VG),Y)
        # $(error STM32F407VG=$(STM32F407VG))
        include $(MICROCONTROLLER_DIR)/stm32f407vg/stm32f407vg_preconfig.mk
    endif

    ifeq ($(AT32F437ZM),Y)
        # $(error AT32F437ZM=$(AT32F437ZM))
        include $(MICROCONTROLLER_DIR)/at32f437zm/at32f437zm_preconfig.mk
    endif

    ifeq ($(YTM32B1ME05G0MLQ),Y)
        # $(error YTM32B1ME05G0MLQ=$(YTM32B1ME05G0MLQ))
        include $(MICROCONTROLLER_DIR)/ytm32b1me05g0mlq/ytm32b1me05g0mlq_preconfig.mk
    endif

    ifeq ($(AT32F4X),Y)
        # $(error AT32F4X=$(AT32F4X))
        include $(MICROCONTROLLER_DIR)/at32f4x/at32f4x_preconfig.mk
    endif
  
endif
