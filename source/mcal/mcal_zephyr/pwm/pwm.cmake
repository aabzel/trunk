
message(STATUS "PWM_ZEPHYR_DRV_MK_INC=${PWM_ZEPHYR_DRV_MK_INC}")
if( NOT (PWM_ZEPHYR_DRV_MK_INC STREQUAL Y))
    set(PWM_ZEPHYR_DRV_MK_INC Y)

    message(STATUS "+ PWM ZEPHYR")
    set(PWM_NRF_DIR ${MCAL_ZEPHYR_DIR}/pwm)
    message(STATUS "PWM_NRF_DIR=${PWM_NRF_DIR}")

    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/drivers/include)
    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/hal)
    target_include_directories(app PUBLIC ${PWM_NRF_DIR})

    #@echo ${error PWM_NRF_DIR=${PWM_NRF_DIR))
    target_compile_definitions(app PUBLIC HAS_PWM)
    #target_compile_definitions(app PUBLIC HAS_PWM_INIT)
    target_compile_definitions(app PUBLIC HAS_PWM_ZEPHYR)
    target_compile_definitions(app PUBLIC HAS_PWM_CUSTOM)

    #message( SEND_ERROR "You can't do that" )
    if (PWM0 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PWM0)
    endif()

    if (PWM1 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PWM1)
    endif()

    if (PWM2 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PWM2)
    endif()

    if (PWM3 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PWM3)
    endif()

    target_sources(app PRIVATE ${PWM_NRF_DIR}/pwm_drv.c)

    if (CLI STREQUAL Y)
        if (PWM_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_PWM_COMMANDS)
            target_sources(app PRIVATE ${PWM_NRF_DIR}/pwm_custom_commands.c)
        endif()
    endif()

    if (DIAG STREQUAL Y)
        if (PWM_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_PWM_DIAG)
            target_sources(app PRIVATE ${PWM_NRF_DIR}/pwm_custom_diag.c)
        endif()
    endif()
endif()
