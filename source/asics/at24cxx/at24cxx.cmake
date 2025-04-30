message(STATUS "AT24CXX_MK_INC=${AT24CXX_MK_INC}")
if( NOT (AT24CXX_MK_INC STREQUAL Y))
    set(AT24CXX_MK_INC Y)
    message(STATUS "+ AT24CXX")

    set(AT24CXX_DIR ${ASICS_DIR}/at24cxx)
    message(STATUS "AT24CXX_DIR=${AT24CXX_DIR}")

    #message( SEND_ERROR "Check Compile" )

    target_compile_definitions(app PUBLIC HAS_AT24CXX)
    target_compile_definitions(app PUBLIC HAS_AT24CXX_PROC)

    target_include_directories(app PUBLIC ${AT24CXX_DIR})

    target_sources(app PRIVATE ${AT24CXX_DIR}/at24cxx_drv.c)
    target_sources(app PRIVATE ${AT24CXX_DIR}/at24cxx_read_drv.c)

    if(AT24CXX_WRITE STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_AT24CXX_WRITE)
        target_sources(app PRIVATE ${AT24CXX_DIR}/at24cxx_write_drv.c)
    endif()

    if(DIAG STREQUAL Y)
        if(AT24CXX_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_AT24CXX_DIAG)
            target_sources(app PRIVATE ${AT24CXX_DIR}/at24cxx_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(AT24CXX_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_AT24CXX_COMMANDS)
            target_sources(app PRIVATE ${AT24CXX_DIR}/at24cxx_commands.c)
        endif()
    endif()
endif()
