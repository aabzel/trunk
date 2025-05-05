message(STATUS "SERIAL_PORT_MK_INC=${SERIAL_PORT_MK_INC}")
if( NOT (SERIAL_PORT_MK_INC STREQUAL Y))
    set(SERIAL_PORT_MK_INC Y)
    set(SERIAL_PORT_DIR ${INTERFACES_DIR}/serial_port)

    message(STATUS "+ SERIAL_PORT")

    target_include_directories(app PUBLIC ${SERIAL_PORT_DIR})
    #target_compile_definitions(app PUBLIC HAS_SERIAL_PORT_PROC)
    target_compile_definitions(app PUBLIC HAS_SERIAL_PORT)

    target_sources(app PRIVATE ${SERIAL_PORT_DIR}/serial_port.c)

    if (DIAG STREQUAL Y)
        if (SERIAL_PORT_DIAG STREQUAL Y)
            message(STATUS "+ SERIAL_PORT_DIAG")
            target_compile_definitions(app PUBLIC HAS_SERIAL_PORT_DIAG)
            target_sources(app PRIVATE ${SERIAL_PORT_DIR}/serial_port_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (SERIAL_PORT_COMMANDS STREQUAL Y)
            message(STATUS "+ SERIAL_PORT_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_SERIAL_PORT_COMMANDS)
        endif()
    endif()
endif()
