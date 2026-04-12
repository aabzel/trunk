if(NOT (LED_GENERAL_MK_INC STREQUAL Y))
    set(LED_GENERAL_MK_INC Y)

    set(LED_GENERAL_DIR "${CONTROL_DIR}/led")

    include_directories( ${LED_GENERAL_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_LED")
    string(APPEND MCAL_OPT " -DHAS_LED_PROC")

    string(APPEND SOURCES_C " ${LED_GENERAL_DIR}/led_drv.c")

    if(LED_MONO STREQUAL Y)
        include(${LED_GENERAL_DIR}/led_mono/led_mono.cmake)
    endif()

    if(LED_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_LED_EXT")
    endif()

    if(LED_RGB STREQUAL Y)
        include(${LED_GENERAL_DIR}/led_rgb/led_rgb.cmake)
    endif()

    if(DIAG STREQUAL Y)
        if(LED_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_LED_DIAG")
            string(APPEND SOURCES_DIAG_C " ${LED_GENERAL_DIR}/led_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(LED_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_LED_COMMANDS")
        endif()
    endif()
endif()
