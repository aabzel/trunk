message(STATUS "SEGGER_RTT_MK_INC=${SEGGER_RTT_MK_INC}")
if( NOT (SEGGER_RTT_MK_INC  STREQUAL  Y))
    set(SEGGER_RTT_MK_INC Y)
    message(STATUS "+ SEGGER_RTT")

    set(SEGGER_RTT_DIR ${ROOT_DIR}/segger_rtt)
    message(STATUS "SEGGER_RTT_DIR=${SEGGER_RTT_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SEGGER_RTT)
    target_compile_definitions(app PUBLIC HAS_SEGGER_RTT)
    target_compile_definitions(app PUBLIC HAS_SEGGER_RTT_PROC)

    target_include_directories(app PUBLIC ${SEGGER_RTT_DIR})
    target_sources(app PRIVATE ${SEGGER_RTT_DIR}/segger_rtt.c)

    if(DIAG  STREQUAL  Y)
        if(SEGGER_RTT_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SEGGER_RTT_DIAG)
            target_sources(app PRIVATE ${SEGGER_RTT_DIR}/segger_rtt_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SEGGER_RTT_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SEGGER_RTT_COMMANDS)
            target_sources(app PRIVATE ${SEGGER_RTT_DIR}/segger_rtt_commands.c)
        endif()
    endif()
endif()
