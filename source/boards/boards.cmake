message(STATUS "BOARDS_MK_INC=${BOARDS_MK_INC}")

if(NOT (BOARDS_MK_INC STREQUAL Y))
    set(BOARDS_MK_INC Y )
    set(BOARD_SELECTED N )

    set(BOARD_DIR "${WORKSPACE_LOC}/boards")

    include_directories(${BOARD_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_BOARD")

    if(AT_START_F413 STREQUAL Y)
        include(${BOARD_DIR}/at_start_f413/at_start_f413.cmake)
    endif()

    if(AT_START_F437 STREQUAL Y)
        include(${BOARD_DIR}/at_start_f437/at_start_f437.cmake)
    endif()

    if(BLE_SPEAKER STREQUAL Y)
        include(${BOARD_DIR}/ble_speaker/ble_speaker.cmake)
    endif()

    if(ERA_3_14_1 STREQUAL Y)
        include(${BOARD_DIR}/era_3_14_1/era_3_14_1.cmake)
    endif()

    if(FLAG_CHIP_EVB_V1 STREQUAL Y)
        include(${BOARD_DIR}/flag_chip_evb_v1/flag_chip_evb_v1.cmake)
    endif()

    if(BLE_AUDIO_EVB_V1 STREQUAL Y)
        include(${BOARD_DIR}/ble_audio_evb_v1/ble_audio_evb_v1.cmake)
    endif()

    if(BT_BLE_UWB_TAG STREQUAL Y)
        include(${BOARD_DIR}/bt_ble_uwb_tag/bt_ble_uwb_tag.cmake)
    endif()

    if(BLACK_PILL_V2_0 STREQUAL Y)
        include(${BOARD_DIR}/black_pill_v2_0/black_pill_v2_0.cmake)
    endif()

    if(BOARD_UTILS STREQUAL Y)
        include(${BOARD_DIR}/board_utils/board_utils.cmake)
    endif()

    if(DUMMY_BOARD STREQUAL Y)
        include(${BOARD_DIR}/dummy_board/dummy_board.cmake)
    endif()

    if(DEV_E_BOX_STM32FXX_M_V3_0 STREQUAL Y)
        include(${BOARD_DIR}/dev_e_box_stm32Fxx_m_v3_0/dev_e_box_stm32Fxx_m_v3_0.cmake)
    endif()

    if(JZ_F407VET6 STREQUAL Y)
        include(${BOARD_DIR}/jz_f407vet6/jz_f407vet6.cmake)
    endif()

    if(MINI_M4 STREQUAL Y)
        include(${BOARD_DIR}/mini_m4/mini_m4.cmake)
    endif()

    if(FC7300_DEMO_BOARD STREQUAL Y)
        include(${BOARD_DIR}/fc7300_demo_board/fc7300_demo_board.cmake)
    endif()

    if(NRF5340_ADK STREQUAL Y)
        include(${BOARD_DIR}/nrf5340_adk/nrf5340_adk.cmake)
    endif()

    if(NRF5340_DK STREQUAL Y)
        include(${BOARD_DIR}/nrf5340_dk/nrf5340_dk.cmake)
    endif()

    if(PASTILDA_R1_1 STREQUAL Y)
        include(${BOARD_DIR}/pastilda_r1_1/pastilda_r1_1.cmake)
    endif()

    if(TERA_TEST STREQUAL Y)
        include(${BOARD_DIR}/tera_test/tera_test.cmake)
    endif()

    if(OLIMEX_H407 STREQUAL Y)
        include(${BOARD_DIR}/olimex_stm32_h407/olimex_stm32_h407.cmake)
    endif()

    if(LAUNCHXL_CC26X2R1 STREQUAL Y)
        include(${BOARD_DIR}/launchpad/launchpad.cmake)
    endif()

    if(NUCLEO_F401RE STREQUAL Y)
        include(${BOARD_DIR}/nucleo_f401re/nucleo_f401re.cmake)
    endif()

    if(START_MIK32_V1 STREQUAL Y)
        include(${BOARD_DIR}/start_mik32_v1/start_mik32_v1.cmake)
    endif()

    if(NUCLEO_F429ZI STREQUAL Y)
        include(${BOARD_DIR}/nucleo_f429zi/nucleo_f429zi.cmake)
    endif()

    if(NUCLEO_F413ZH STREQUAL Y)
        include(${BOARD_DIR}/nucleo_f413zh/nucleo_f413zh.cmake)
    endif()

    if(NUCLEO_F446RE STREQUAL Y)
        include(${BOARD_DIR}/nucleo_f446re/nucleo_f446re.cmake)
    endif()

    if(NUCLEO_L073RZ STREQUAL Y)
        include(${BOARD_DIR}/nucleo_l073rz/nucleo_l073rz.cmake)
    endif()

    if(K098A STREQUAL Y)
        include(${BOARD_DIR}/pcan_pro_x/pcan_pro_x.cmake)
    endif()

    if(SMARTPHONE_STATION STREQUAL Y)
        include(${BOARD_DIR}/smartphone_station/smartphone_station.cmake)
    endif()

    if(STM32_F4VE STREQUAL Y)
        include(${BOARD_DIR}/stm32_f4ve/stm32_f4ve.cmake)
    endif()

    if(X86 STREQUAL Y)
        include(${BOARD_DIR}/x86/x86.cmake)
    endif()

    if(YTM32B1M_EVB_0144_REV_B STREQUAL Y)
        include(${BOARD_DIR}/ytm32b1m_evb_0144_rev_b/ytm32b1m_evb_0144_rev_b.cmake)
    endif()

    if(NOT (BOARD_SELECTED STREQUAL Y))
        message(FATAL_ERROR "Select Board")
    endif()
endif()
