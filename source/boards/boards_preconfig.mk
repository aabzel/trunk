$(info BOARDS_PRECONFIG_MK_INC=$(BOARDS_PRECONFIG_MK_INC))

ifneq ($(BOARDS_PRECONFIG_MK_INC),Y)
    BOARDS_PRECONFIG_MK_INC=Y

    BOARD_DIR = $(WORKSPACE_LOC)/boards
    # $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    # $(error BOARD_DIR=$(BOARD_DIR))

    ifeq ($(AT_START_F413),Y)
        # $(error AT_START_F413=$(AT_START_F413))
        include $(BOARD_DIR)/at_start_f413/at_start_f413_preconfig.mk
    endif

    ifeq ($(JZ_F407VET6),Y)
        # $(error JZ_F407VET6=$(JZ_F407VET6))
        include $(BOARD_DIR)/jz_f407vet6/jz_f407vet6_preconfig.mk
    endif

    ifeq ($(TERA_TEST),Y)
        # $(error TERA_TEST=$(TERA_TEST))
        include $(BOARD_DIR)/tera_test/tera_test_preconfig.mk
    endif

    ifeq ($(AT_START_F437),Y)
        # $(error AT_START_F437=$(AT_START_F437))
        include $(BOARD_DIR)/at_start_f437/at_start_f437_preconfig.mk
    endif

    ifeq ($(BLE_SPEAKER),Y)
        # $(error BLE_SPEAKER=$(BLE_SPEAKER))
        include $(BOARD_DIR)/ble_speaker/ble_speaker_preconfig.mk
    endif

    ifeq ($(BLE_AUDIO_EVB_V1),Y)
        # $(error BLE_AUDIO_EVB_V1=$(BLE_AUDIO_EVB_V1))
        include $(BOARD_DIR)/ble_audio_evb_v1/ble_audio_evb_v1_preconfig.mk
    endif

    ifeq ($(BT_BLE_UWB_TAG),Y)
        # $(error BT_BLE_UWB_TAG=$(BT_BLE_UWB_TAG))
        include $(BOARD_DIR)/bt_ble_uwb_tag/bt_ble_uwb_tag_preconfig.mk
    endif

    ifeq ($(BOARD_UTILS),Y)
        # $(error BOARD_UTILS=$(BOARD_UTILS))
        include $(BOARD_DIR)/board_utils/board_utils_preconfig.mk
    endif

    ifeq ($(X86),Y)
        # $(error X86=$(X86))
        include $(BOARD_DIR)/x86/x86_preconfig.mk
    endif

    ifeq ($(NRF5340_ADK),Y)
        # $(error NRF5340_ADK=$(NRF5340_ADK))
        include $(BOARD_DIR)/nrf5340_adk/nrf5340_adk_preconfig.mk
    endif

    ifeq ($(PCAN_PRO_X),Y)
        # $(error PCAN_PRO_X=$(PCAN_PRO_X))
        include $(BOARD_DIR)/pcan_pro_x/pcan_pro_x_preconfig.mk
    endif

    ifeq ($(NRF5340_DK),Y)
        # $(error NRF5340_DK=$(NRF5340_DK))
        include $(BOARD_DIR)/nrf5340_dk/nrf5340_dk_preconfig.mk
    endif

    ifeq ($(PASTILDA_R1_1),Y)
        # $(error PASTILDA_R1_1=$(PASTILDA_R1_1))
        include $(BOARD_DIR)/pastilda_r1_1/pastilda_r1_1_preconfig.mk
    endif

    ifeq ($(MINI_M4),Y)
        # $(error MINI_M4=$(MINI_M4))
        include $(BOARD_DIR)/mini_m4/mini_m4_preconfig.mk
    endif

    ifeq ($(OLIMEX_H407),Y)
        # $(error OLIMEX_H407=$(OLIMEX_H407))
        include $(BOARD_DIR)/olimex_stm32_h407/olimex_stm32_h407_preconfig.mk
    endif

    ifeq ($(LAUNCHXL_CC26X2R1),Y)
        # $(error NUCLEO_F413ZH=$(NUCLEO_F413ZH))
        include $(BOARD_DIR)/launchpad/launchpad_preconfig.mk
    endif

    ifeq ($(NUCLEO_F401RE),Y)
        # $(error NUCLEO_F401RE=$(NUCLEO_F401RE))
        include $(BOARD_DIR)/nucleo_f401re/nucleo_f401re_preconfig.mk
    endif

    ifeq ($(NUCLEO_F413ZH),Y)
        # $(error NUCLEO_F413ZH=$(NUCLEO_F413ZH))
        include $(BOARD_DIR)/nucleo_f413zh/nucleo_f413zh_preconfig.mk
    endif

    ifeq ($(NUCLEO_F446RE),Y)
        # $(error NUCLEO_F446RE=$(NUCLEO_F446RE))
        include $(BOARD_DIR)/nucleo_f446re/nucleo_f446re_preconfig.mk
    endif

    ifeq ($(NUCLEO_L073RZ),Y)
        # $(error NUCLEO_L073RZ=$(NUCLEO_L073RZ))
        include $(BOARD_DIR)/nucleo_l073rz/nucleo_l073rz_preconfig.mk
    endif

    ifeq ($(SMARTPHONE_STATION),Y)
        # $(error SMARTPHONE_STATION=$(SMARTPHONE_STATION))
        include $(BOARD_DIR)/smartphone_station/smartphone_station_preconfig.mk
    endif

    ifeq ($(BLACK_PILL_V2_0),Y)
        # $(error BLACK_PILL_V2_0=$(BLACK_PILL_V2_0))
        include $(BOARD_DIR)/black_pill_v2_0/black_pill_v2_0_preconfig.mk
    endif
endif
