$(info MICROCONTROLLER_MK_INC= $(MICROCONTROLLER_MK_INC))
ifneq ($(MICROCONTROLLER_MK_INC),Y)
    MICROCONTROLLER_MK_INC=Y
    MICROCONTROLLER_SELECTED=N

    MICROCONTROLLER_DIR = $(WORKSPACE_LOC)/microcontroller
    # $(error MICROCONTROLLER_DIR= $(MICROCONTROLLER_DIR))

    INCDIR += -I$(MICROCONTROLLER_DIR)

    MICROCONTROLLER=Y
    MCAL_OPT += -DHAS_MICROCONTROLLER

    SOURCES_C += $(MICROCONTROLLER_DIR)/microcontroller_drv.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(MICROCONTROLLER_DIR)/microcontroller_diag.c
    endif

    ifeq ($(CLI),Y)
        SOURCES_C += $(MICROCONTROLLER_DIR)/microcontroller_commands.c
    endif
    
    ifeq ($(MCU_X86),Y)
        #$(error X86= $(X86))
        include $(MICROCONTROLLER_DIR)/x86/cpu_x86.mk
    endif

    ifeq ($(AT32F413RC),Y)
        # $(error AT32F413RC= $(AT32F413RC))
        include $(MICROCONTROLLER_DIR)/at32f413rc/at32f413rc.mk
    endif

    ifeq ($(K1948BK018),Y)
        # $(error K1948BK018= $(K1948BK018))
        include $(MICROCONTROLLER_DIR)/k1948bk018/k1948bk018.mk
    endif

    ifeq ($(AT32F435ZM),Y)
        # $(error AT32F435ZM= $(AT32F435ZM))
        include $(MICROCONTROLLER_DIR)/at32f435zm/at32f435zm.mk
    endif

    ifeq ($(AT32F437ZM),Y)
        # $(error AT32F437ZM= $(AT32F437ZM))
        include $(MICROCONTROLLER_DIR)/at32f437zm/at32f437zm.mk
    endif

    ifeq ($(AT32F4X),Y)
        # $(error AT32F4X= $(AT32F4X))
        include $(MICROCONTROLLER_DIR)/at32f4x/at32f4x.mk
    endif
    
    ifeq ($(CC2642R1F),Y)
        # $(error CC2642R1F=$(CC2642R1F))
        include $(MICROCONTROLLER_DIR)/cc2642r1f/cc2642r1f.mk
    endif

    ifeq ($(CC2652R1F),Y)
        # $(error CC2652R1F=$(CC2652R1F))
        include $(MICROCONTROLLER_DIR)/cc2652r1f/cc2652r1f.mk
    endif

    ifeq ($(DUMMY_MCU),Y)
        # $(error DUMMY_MCU=$(DUMMY_MCU))
        include $(MICROCONTROLLER_DIR)/dummy_mcu/dummy_mcu.mk
    endif

    ifeq ($(FC7300F8MDT),Y)
        # $(error FC7300F8MDT=$(FC7300F8MDT))
        include $(MICROCONTROLLER_DIR)/fc7300f8mdt/fc7300f8mdt.mk
    endif

    ifeq ($(NRF5340),Y)
        # $(error NRF5340=$(NRF5340))
        include $(MICROCONTROLLER_DIR)/nrf5340/nrf5340.mk
    endif

    ifeq ($(STM32F401RE),Y)
        # $(error STM32F401RE= $(STM32F401RE))
        include $(MICROCONTROLLER_DIR)/stm32f401re/stm32f401re.mk
    endif

    ifeq ($(STM32F407VE),Y)
        # $(error STM32F407VE= $(STM32F407VE))
        include $(MICROCONTROLLER_DIR)/stm32f407ve/stm32f407ve.mk
    endif

    ifeq ($(STM32F407VG),Y)
        # $(error STM32F407VG= $(STM32F407VG))
        include $(MICROCONTROLLER_DIR)/stm32f407vg/stm32f407vg.mk
    endif

    ifeq ($(STM32F407ZG),Y)
        # $(error STM32F407ZG=$(STM32F407ZG))
        include $(MICROCONTROLLER_DIR)/stm32f407zg/stm32f407zg.mk
    endif

    ifeq ($(STM32F411CE),Y)
        include $(MICROCONTROLLER_DIR)/stm32f411ce/stm32f411ce.mk
    endif

    ifeq ($(STM32F413ZH),Y)
        include $(MICROCONTROLLER_DIR)/stm32f413zh/stm32f413zh.mk
    endif

    ifeq ($(STM32F415RG),Y)
        # $(error STM32F415RG=$(STM32F415RG))
        include $(MICROCONTROLLER_DIR)/stm32f415rg/stm32f415rg.mk
    endif

    ifeq ($(STM32F429ZI),Y)
        include $(MICROCONTROLLER_DIR)/stm32f429zi/stm32f429zi.mk
    endif

    ifeq ($(STM32F446RE),Y)
        include $(MICROCONTROLLER_DIR)/stm32f446re/stm32f446re.mk
    endif

    ifeq ($(STM32F746ZG),Y)
        include $(MICROCONTROLLER_DIR)/stm32f746zg/stm32f746zg.mk
    endif

    ifeq ($(STM32L073RZ),Y)
        include $(MICROCONTROLLER_DIR)/stm32l073rz/stm32l073rz.mk
    endif

    ifeq ($(X86),Y)
        include $(MICROCONTROLLER_DIR)/x86/cpu_x86.mk
        MICROCONTROLLER_SELECTED=Y
    endif

    ifeq ($(YTM32B1ME05G0MLQ),Y)
        # $(error YTM32B1ME05G0MLQ=$(YTM32B1ME05G0MLQ))
        include $(MICROCONTROLLER_DIR)/ytm32b1me05g0mlq/ytm32b1me05g0mlq.mk
    endif

    ifneq ($(MICROCONTROLLER_SELECTED),Y)
        $(error Select MCU)
    endif
endif
