#message(STATUS "MCAL_MK_INC=${MCAL_MK_INC}")
if( NOT (MCAL_MK_INC STREQUAL Y))
    set(MCAL_MK_INC Y)

    #message("Add MCAL")

    set(MCAL_DIR ${WORKSPACE_LOC}/mcal)
    get_filename_component(MCAL_DIR ${MCAL_DIR} REALPATH)

    string(APPEND MCAL_OPT " -DHAS_MCAL")
    include_directories( ${MCAL_DIR})

    if(MCAL STREQUAL Y)
        include(${MCAL_DIR}/mcal_common/mcal_common.cmake)
    endif()

    if(EHAL_MCAL STREQUAL Y)
        include(${MCAL_DIR}/ehal_mcal/ehal_mcal.cmake)
    endif()
    
    if(MCAL_AT32 STREQUAL Y)
        include(${MCAL_DIR}/mcal_at32f4/mcal_at32f4.cmake)
    endif()

    if(MCAL_X86 STREQUAL Y)
        include(${MCAL_DIR}/mcal_x86/mcal_x86.cmake)
    endif()
    
    if(MCAL_CC26X2 STREQUAL Y)
        include(${MCAL_DIR}/mcal_cc26x2/mcal_cc26x2.cmake)
    endif()

    if(MCAL_EHAL STREQUAL Y)
        include(${MCAL_DIR}/mcal_ehal/mcal_ehal.cmake)
    endif()

    if(MCAL_ESP32 STREQUAL Y)
        include(${MCAL_DIR}/mcal_esp32/mcal_esp32.cmake)
    endif()

    if(MCAL_FC7300X STREQUAL Y)
        include(${MCAL_DIR}/mcal_fc7300x/mcal_fc7300x.cmake)
    endif()

    if(MCAL_MIK32 STREQUAL Y)
        include(${MCAL_DIR}/mcal_mik32/mcal_mik32.cmake)
    endif()

    if(MCAL_FLAGSHIP STREQUAL Y)
        include(${MCAL_DIR}/mcal_flagship/mcal_flagship.cmake)
    endif()

    if(MCAL_NRF5340 STREQUAL Y)
        message(STATUS "+ MCAL_NRF5340")
        include(${MCAL_DIR}/mcal_nrf5340/mcal_nrf5340.cmake)
    endif()

    if(MCAL_YUNTU STREQUAL Y)
        include(${MCAL_DIR}/mcal_yuntu/mcal_yuntu.cmake)
    endif()
    
    if(MCAL_STM32 STREQUAL Y)
        include(${MCAL_DIR}/mcal_stm32f4/mcal_stm32f4.cmake)
    endif()

    if(MCAL_ZEPHYR STREQUAL Y)
        include(${MCAL_DIR}/mcal_zephyr/mcal_zephyr.cmake)
    endif()

endif()
