
if( NOT (LED_MONO_MK_INC STREQUAL Y))
    set(LED_MONO_MK_INC Y)

    set(LED_MONO_DIR "${LED_GENERAL_DIR}/led_mono")

    include_directories( ${LED_MONO_DIR})
    
    string(APPEND INCDIR " ${LED_MONO_DIR}")

    string(APPEND SOURCES_C " ${LED_MONO_DIR}/led_mono_drv.c")

    if(PWM STREQUAL Y)
        string(APPEND SOURCES_C " ${LED_MONO_DIR}/led_mono_pwm.c")
    endif()

    string(APPEND MCAL_OPT " -DHAS_LED_MONO")
    string(APPEND MCAL_OPT " -DHAS_LED_MONO_PROC")

    if(DIAG STREQUAL Y)
        if(LED_MONO_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_LED_MONO_DIAG")
            string(APPEND SOURCES_C " ${LED_MONO_DIR}/led_mono_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(LED_MONO_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_LED_MONO_COMMANDS")
            string(APPEND SOURCES_C " ${LED_MONO_DIR}/led_mono_commands.c")
        endif()
    endif()
endif()
