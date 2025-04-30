message(STATUS "LED_GENERAL_MK_INC=${LED_GENERAL_MK_INC}")
if( NOT (LED_GENERAL_MK_INC  STREQUAL  Y))
    set(LED_GENERAL_MK_INC Y)
    message(STATUS "+ LED General")

    set(LED_GENERAL_DIR ${CONTROL_DIR}/led)
    message(STATUS "LED_GENERAL_DIR=${LED_GENERAL_DIR}")

    add_compile_definitions(HAS_LED)
    target_compile_definitions(app PUBLIC HAS_LED)
    target_include_directories(app PUBLIC ${LED_GENERAL_DIR})

    target_sources(app PRIVATE ${LED_GENERAL_DIR}/led_drv.c)

    if(LED_PROC STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_LED_PROC)
    endif()

    if(LED_MONO STREQUAL  Y)
        message(STATUS "+ Mono LED")
        include(${LED_GENERAL_DIR}/led_mono/led_mono.cmake)
    endif()

    if(DIAG STREQUAL  Y)
        if(LED_DIAG  STREQUAL  Y)
            message(STATUS "+ LED Diag")
            target_compile_definitions(app PUBLIC HAS_LED_DIAG)
            target_sources(app PRIVATE ${LED_GENERAL_DIR}/led_diag.c)
        endif()
    endif()

    if(LED_RGB  STREQUAL  Y)
        message(STATUS "+ RGB LED")
        include(${LED_GENERAL_DIR}/led_rgb/led_rgb.cmake)
    endif()
    
    if(INDICATION  STREQUAL  Y)
        message(STATUS "+ indication")
        include(${LED_GENERAL_DIR}/indication/indication.cmake)
    endif()

endif()
