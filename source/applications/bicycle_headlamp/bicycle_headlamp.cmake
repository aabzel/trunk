message(STATUS "BICYCLE_HEADLAMP_MK_INC=${BICYCLE_HEADLAMP_MK_INC}")
if( NOT (BICYCLE_HEADLAMP_MK_INC  STREQUAL  Y))
    set(BICYCLE_HEADLAMP_MK_INC Y)
    message(STATUS "+ BICYCLE_HEADLAMP")

    set(BICYCLE_HEADLAMP_DIR ${ROOT_DIR}/bicycle_headlamp)
    message(STATUS "BICYCLE_HEADLAMP_DIR=${BICYCLE_HEADLAMP_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_BICYCLE_HEADLAMP)
    target_compile_definitions(app PUBLIC HAS_BICYCLE_HEADLAMP)
    target_compile_definitions(app PUBLIC HAS_BICYCLE_HEADLAMP_PROC)

    target_include_directories(app PUBLIC ${BICYCLE_HEADLAMP_DIR})
    target_sources(app PRIVATE ${BICYCLE_HEADLAMP_DIR}/bicycle_headlamp.c)

    if(DIAG  STREQUAL  Y)
        if(BICYCLE_HEADLAMP_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BICYCLE_HEADLAMP_DIAG)
            target_sources(app PRIVATE ${BICYCLE_HEADLAMP_DIR}/bicycle_headlamp_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(BICYCLE_HEADLAMP_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BICYCLE_HEADLAMP_COMMANDS)
            target_sources(app PRIVATE ${BICYCLE_HEADLAMP_DIR}/bicycle_headlamp_commands.c)
        endif()
    endif()
endif()
