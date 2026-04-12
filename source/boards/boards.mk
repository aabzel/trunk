$(info BOARDS_MK_INC=$(BOARDS_MK_INC))

ifneq ($(BOARDS_MK_INC),Y)
    BOARDS_MK_INC=Y
    BOARD_SELECTED=N

    BOARD_DIR = $(WORKSPACE_LOC)/boards
    # $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    # $(error BOARD_DIR=$(BOARD_DIR))

    MCAL_OPT += -DHAS_BOARD
    INCDIR += -I$(BOARD_DIR)

    #include $(BOARD_DIR)/sw_config/sw_config.mk

    ifeq ($(AT_START_F413),Y)
        # $(error AT_START_F413=$(AT_START_F413))
        include $(BOARD_DIR)/at_start_f413/at_start_f413.mk
    endif

    ifeq ($(AT_START_F437),Y)
        # $(error AT_START_F437=$(AT_START_F437))
        include $(BOARD_DIR)/at_start_f437/at_start_f437.mk
    endif
    
    ifeq ($(BLE_SPEAKER),Y)
        # $(error BLE_SPEAKER=$(BLE_SPEAKER))
        include $(BOARD_DIR)/ble_speaker/ble_speaker.mk
    endif

    ifeq ($(ERA_3_14_1),Y)
        # $(error ERA_3_14_1=$(ERA_3_14_1))
        include $(BOARD_DIR)/era_3_14_1/era_3_14_1.mk
    endif

    ifeq ($(FLAG_CHIP_EVB_V1),Y)
        # $(error FLAG_CHIP_EVB_V1=$(FLAG_CHIP_EVB_V1))
        include $(BOARD_DIR)/flag_chip_evb_v1/flag_chip_evb_v1.mk
    endif

    ifeq ($(BLE_AUDIO_EVB_V1),Y)
        # $(error BLE_AUDIO_EVB_V1=$(BLE_AUDIO_EVB_V1))
        include $(BOARD_DIR)/ble_audio_evb_v1/ble_audio_evb_v1.mk
    endif

    ifeq ($(BT_BLE_UWB_TAG),Y)
        # $(error BT_BLE_UWB_TAG=$(BT_BLE_UWB_TAG))
        include $(BOARD_DIR)/bt_ble_uwb_tag/bt_ble_uwb_tag.mk
    endif

    ifeq ($(BLACK_PILL_V2_0),Y)
        # $(error BLACK_PILL_V2_0=$(BLACK_PILL_V2_0))
        include $(BOARD_DIR)/black_pill_v2_0/black_pill_v2_0.mk
    endif

    ifeq ($(BOARD_UTILS),Y)
        # $(error BOARD_UTILS=$(BOARD_UTILS))
        include $(BOARD_DIR)/board_utils/board_utils.mk
    endif

    ifeq ($(DUMMY_BOARD),Y)
        # $(error DUMMY_BOARD=$(DUMMY_BOARD))
        include $(BOARD_DIR)/dummy_board/dummy_board.mk
    endif

    ifeq ($(DEV_E_BOX_STM32FXX_M_V3_0),Y)
        # $(error DEV_E_BOX_STM32FXX_M_V3_0=$(DEV_E_BOX_STM32FXX_M_V3_0))
        include $(BOARD_DIR)/dev_e_box_stm32Fxx_m_v3_0/dev_e_box_stm32Fxx_m_v3_0.mk
    endif

    ifeq ($(JZ_F407VET6),Y)
        # $(error JZ_F407VET6=$(JZ_F407VET6))
        include $(BOARD_DIR)/jz_f407vet6/jz_f407vet6.mk
    endif

    ifeq ($(MINI_M4),Y)
        # $(error MINI_M4=$(MINI_M4))
        include $(BOARD_DIR)/mini_m4/mini_m4.mk
    endif

    ifeq ($(FC7300_DEMO_BOARD),Y)
        # $(error FC7300_DEMO_BOARD=$(FC7300_DEMO_BOARD))
        include $(BOARD_DIR)/fc7300_demo_board/fc7300_demo_board.mk
    endif
    
    ifeq ($(NRF5340_ADK),Y)
        # $(error NRF5340_ADK=$(NRF5340_ADK))
        include $(BOARD_DIR)/nrf5340_adk/nrf5340_adk.mk
    endif

    ifeq ($(NRF5340_DK),Y)
        # $(error NRF5340_DK=$(NRF5340_DK))
        include $(BOARD_DIR)/nrf5340_dk/nrf5340_dk.mk
    endif

    ifeq ($(PASTILDA_R1_1),Y)
        # $(error PASTILDA_R1_1=$(PASTILDA_R1_1))
        include $(BOARD_DIR)/pastilda_r1_1/pastilda_r1_1.mk
    endif

    ifeq ($(TERA_TEST),Y)
        # $(error TERA_TEST=$(TERA_TEST))
        include $(BOARD_DIR)/tera_test/tera_test.mk
    endif

    ifeq ($(OLIMEX_H407),Y)
        # $(error OLIMEX_H407=$(OLIMEX_H407))
        include $(BOARD_DIR)/olimex_stm32_h407/olimex_stm32_h407.mk
    endif

    ifeq ($(LAUNCHXL_CC26X2R1),Y)
        # $(error NUCLEO_F413ZH=$(NUCLEO_F413ZH))
        include $(BOARD_DIR)/launchpad/launchpad.mk
    endif

    ifeq ($(NUCLEO_F401RE),Y)
        # $(error NUCLEO_F401RE=$(NUCLEO_F401RE))
        include $(BOARD_DIR)/nucleo_f401re/nucleo_f401re.mk
    endif
    
    ifeq ($(START_MIK32_V1),Y)
        # $(error START_MIK32_V1=$(START_MIK32_V1))
        include $(BOARD_DIR)/start_mik32_v1/start_mik32_v1.mk
    endif

    ifeq ($(NUCLEO_F429ZI),Y)
        # $(error NUCLEO_F429ZI=$(NUCLEO_F429ZI))
        include $(BOARD_DIR)/nucleo_f429zi/nucleo_f429zi.mk
    endif

    ifeq ($(NUCLEO_F413ZH),Y)
        # $(error NUCLEO_F413ZH=$(NUCLEO_F413ZH))
        include $(BOARD_DIR)/nucleo_f413zh/nucleo_f413zh.mk
    endif

    ifeq ($(NUCLEO_F446RE),Y)
        # $(error NUCLEO_F446RE=$(NUCLEO_F446RE))
        include $(BOARD_DIR)/nucleo_f446re/nucleo_f446re.mk
    endif

    ifeq ($(NUCLEO_L073RZ),Y)
        # $(error NUCLEO_L073RZ=$(NUCLEO_L073RZ))
        include $(BOARD_DIR)/nucleo_l073rz/nucleo_l073rz.mk
    endif

    ifeq ($(K098A),Y)
        # $(error K098A=$(K098A))
        include $(BOARD_DIR)/pcan_pro_x/pcan_pro_x.mk
    endif
    
    ifeq ($(SMARTPHONE_STATION),Y)
        # $(error SMARTPHONE_STATION=$(SMARTPHONE_STATION))
        include $(BOARD_DIR)/smartphone_station/smartphone_station.mk
    endif

    ifeq ($(STM32_F4VE),Y)
        # $(error STM32_F4VE=$(STM32_F4VE))
        include $(BOARD_DIR)/stm32_f4ve/stm32_f4ve.mk
    endif

    ifeq ($(X86),Y)
        # $(error X86=$(X86))
        include $(BOARD_DIR)/x86/x86.mk
    endif

    ifeq ($(YTM32B1M_EVB_0144_REV_B),Y)
        # $(error YTM32B1M_EVB_0144_REV_B=$(YTM32B1M_EVB_0144_REV_B))
        include $(BOARD_DIR)/ytm32b1m_evb_0144_rev_b/ytm32b1m_evb_0144_rev_b.mk
    endif

    ifneq ($(BOARD_SELECTED),Y)
        $(error Select Board)
    endif
endif
