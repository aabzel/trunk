message(STATUS "PWM_PHASE_DEMO_MK_INC=${PWM_PHASE_DEMO_MK_INC}")
if( NOT (PWM_PHASE_DEMO_MK_INC  STREQUAL  Y))
    set(PWM_PHASE_DEMO_MK_INC Y)
    message(STATUS "+ PWM_PHASE_DEMO")

    set(PWM_PHASE_DEMO_DIR ${ROOT_DIR}/pwm_phase_demo)
    message(STATUS "PWM_PHASE_DEMO_DIR=${PWM_PHASE_DEMO_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_PWM_PHASE_DEMO)
    target_compile_definitions(app PUBLIC HAS_PWM_PHASE_DEMO)
    target_compile_definitions(app PUBLIC HAS_PWM_PHASE_DEMO_PROC)

    target_include_directories(app PUBLIC ${PWM_PHASE_DEMO_DIR})
    target_sources(app PRIVATE ${PWM_PHASE_DEMO_DIR}/pwm_phase_demo.c)

    if(DIAG  STREQUAL  Y)
        if(PWM_PHASE_DEMO_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_PWM_PHASE_DEMO_DIAG)
            target_sources(app PRIVATE ${PWM_PHASE_DEMO_DIR}/pwm_phase_demo_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(PWM_PHASE_DEMO_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_PWM_PHASE_DEMO_COMMANDS)
            target_sources(app PRIVATE ${PWM_PHASE_DEMO_DIR}/pwm_phase_demo_commands.c)
        endif()
    endif()
endif()
