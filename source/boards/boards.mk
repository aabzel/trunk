$(info BOARDS_MK_INC=$(BOARDS_MK_INC))

ifneq ($(BOARDS_MK_INC),Y)
    BOARDS_MK_INC=Y
    BOARD_SELECTED=N

    BOARD_DIR = $(WORKSPACE_LOC)/boards
    #@echo $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    #@echo $(error BOARD_DIR=$(BOARD_DIR))

    OPT += -DHAS_BOARD
    INCDIR += -I$(BOARD_DIR)

    #include $(BOARD_DIR)/sw_config/sw_config.mk

    ifeq ($(AT_START_F413),Y)
        #@echo $(error AT_START_F413=$(AT_START_F413))
        include $(BOARD_DIR)/at_start_f413/at_start_f413.mk
    endif

    ifeq ($(AT_START_F437),Y)
        #@echo $(error AT_START_F437=$(AT_START_F437))
        include $(BOARD_DIR)/at_start_f437/at_start_f437.mk
    endif

    ifeq ($(START_MIK32_V1),Y)
        #@echo $(error START_MIK32_V1=$(START_MIK32_V1))
        include $(BOARD_DIR)/start_mik32_v1/start_mik32_v1.mk
    endif

    ifeq ($(STM32_F4VE),Y)
        #@echo $(error STM32_F4VE=$(STM32_F4VE))
        include $(BOARD_DIR)/stm32_f4ve/stm32_f4ve.mk
    endif

    ifeq ($(BLACK_PILL_V2_0),Y)
        #@echo $(error BLACK_PILL_V2_0=$(BLACK_PILL_V2_0))
        include $(BOARD_DIR)/black_pill_v2_0/black_pill_v2_0.mk
    endif

    ifeq ($(BOARD_UTILS),Y)
        #@echo $(error BOARD_UTILS=$(BOARD_UTILS))
        include $(BOARD_DIR)/board_utils/board_utils.mk
    endif

    ifeq ($(DEV_E_BOX_STM32FXX_M_V3_0),Y)
        #@echo $(error DEV_E_BOX_STM32FXX_M_V3_0=$(DEV_E_BOX_STM32FXX_M_V3_0))
        include $(BOARD_DIR)/dev_e_box_stm32Fxx_m_v3_0/dev_e_box_stm32Fxx_m_v3_0.mk
    endif

    ifeq ($(MINI_M4),Y)
        #@echo $(error MINI_M4=$(MINI_M4))
        include $(BOARD_DIR)/mini_m4/mini_m4.mk
    endif

    ifeq ($(NRF5340_ADK),Y)
        #@echo $(error NRF5340_ADK=$(NRF5340_ADK))
        include $(BOARD_DIR)/nrf5340_adk/nrf5340_adk.mk
    endif

    ifeq ($(NRF5340_DK),Y)
        #@echo $(error NRF5340_DK=$(NRF5340_DK))
        include $(BOARD_DIR)/nrf5340_dk/nrf5340_dk.mk
    endif

    ifeq ($(OLIMEX_H407),Y)
        #@echo $(error OLIMEX_H407=$(OLIMEX_H407))
        include $(BOARD_DIR)/olimex_stm32_h407/olimex_stm32_h407.mk
    endif

    ifeq ($(LAUNCHXL_CC26X2R1),Y)
        #@echo $(error NUCLEO_F413ZH=$(NUCLEO_F413ZH))
        include $(BOARD_DIR)/launchpad/launchpad.mk
    endif

    ifeq ($(NUCLEO_F401RE),Y)
        #@echo $(error NUCLEO_F401RE=$(NUCLEO_F401RE))
        include $(BOARD_DIR)/nucleo_f401re/nucleo_f401re.mk
    endif

    ifeq ($(NUCLEO_F429ZI),Y)
        #@echo $(error NUCLEO_F429ZI=$(NUCLEO_F429ZI))
        include $(BOARD_DIR)/nucleo_f429zi/nucleo_f429zi.mk
    endif

    ifeq ($(NUCLEO_F413ZH),Y)
        #@echo $(error NUCLEO_F413ZH=$(NUCLEO_F413ZH))
        include $(BOARD_DIR)/nucleo_f413zh/nucleo_f413zh.mk
    endif

    ifeq ($(NUCLEO_F446RE),Y)
        #@echo $(error NUCLEO_F446RE=$(NUCLEO_F446RE))
        include $(BOARD_DIR)/nucleo_f446re/nucleo_f446re.mk
    endif

    ifeq ($(NUCLEO_L073RZ),Y)
        #@echo $(error NUCLEO_L073RZ=$(NUCLEO_L073RZ))
        include $(BOARD_DIR)/nucleo_l073rz/nucleo_l073rz.mk
    endif

    ifeq ($(X86),Y)
        #@echo $(error X86=$(X86))
        include $(BOARD_DIR)/x86/x86.mk
    endif

    ifeq ($(YTM32B1M_EVB_0144_REV_B),Y)
        #@echo $(error YTM32B1M_EVB_0144_REV_B=$(YTM32B1M_EVB_0144_REV_B))
        include $(BOARD_DIR)/ytm32b1m_evb_0144_rev_b/ytm32b1m_evb_0144_rev_b.mk
    endif

    ifneq ($(BOARD_SELECTED),Y)
        @echo $(error Select Board)
    endif
endif
