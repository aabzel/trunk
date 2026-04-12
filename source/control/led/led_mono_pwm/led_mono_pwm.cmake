message(STATUS "LED_MONO_PWM_MK_INC=${LED_MONO_PWM_MK_INC}")
if( NOT (LED_MONO_PWM_MK_INC  STREQUAL  Y))
    set(LED_MONO_PWM_MK_INC Y)
    message(STATUS "+ LED_MONO_PWM")

    set(LED_MONO_PWM_DIR ${ROOT_DIR}/led_mono_pwm)
    message(STATUS "LED_MONO_PWM_DIR=${LED_MONO_PWM_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_LED_MONO_PWM)
    target_compile_definitions(app PUBLIC HAS_LED_MONO_PWM)
    target_compile_definitions(app PUBLIC HAS_LED_MONO_PWM_PROC)

    target_include_directories(app PUBLIC ${LED_MONO_PWM_DIR})
    target_sources(app PRIVATE ${LED_MONO_PWM_DIR}/led_mono_pwm.c)

    if(DIAG  STREQUAL  Y)
        if(LED_MONO_PWM_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LED_MONO_PWM_DIAG)
            target_sources(app PRIVATE ${LED_MONO_PWM_DIR}/led_mono_pwm_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(LED_MONO_PWM_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LED_MONO_PWM_COMMANDS)
            target_sources(app PRIVATE ${LED_MONO_PWM_DIR}/led_mono_pwm_commands.c)
        endif()
    endif()
endif()
