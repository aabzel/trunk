
message(STATUS "PWM_MCAL_MK_INC=${PWM_MCAL_MK_INC}")

if( NOT (PWM_MCAL_MK_INC STREQUAL Y))
    set(PWM_MCAL_MK_INC Y)

    message(STATUS "+PWM Common Drv")

    set(PWM_MCAL_DIR ${MCAL_COMMON_DIR}/pwm)
    #@echo ${error PWM_MCAL_DIR=${PWM_MCAL_DIR))

    target_include_directories(app PUBLIC ${PWM_MCAL_DIR})

    target_compile_definitions(app PUBLIC HAS_PWM)

    target_sources(app PRIVATE ${PWM_MCAL_DIR}/pwm_general_drv.c)

    if (DIAG STREQUAL Y)
        if (PWM_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_PWM_DIAG)
            target_sources(app PRIVATE ${PWM_MCAL_DIR}/pwm_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        #@echo ${error CLI=${CLI))
        if (PWM_COMMANDS STREQUAL Y)
            #@echo ${error PWM_COMMANDS=${PWM_COMMANDS))
            target_compile_definitions(app PUBLIC HAS_PWM_COMMANDS)
            target_sources(app PRIVATE ${PWM_MCAL_DIR}/pwm_commands.c)
        endif()
    endif()
endif()


