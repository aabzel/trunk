message(STATUS "MX25L6433F_MK_INC=${MX25L6433F_MK_INC}")
if( NOT (MX25L6433F_MK_INC  STREQUAL  Y))
    set(MX25L6433F_MK_INC Y)
    message(STATUS "+ MX25L6433F")

    set(MX25L6433F_DIR ${ROOT_DIR}/mx25l6433f)
    message(STATUS "MX25L6433F_DIR=${MX25L6433F_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_MX25L6433F)
    target_compile_definitions(app PUBLIC HAS_MX25L6433F)
    target_compile_definitions(app PUBLIC HAS_MX25L6433F_PROC)

    target_include_directories(app PUBLIC ${MX25L6433F_DIR})
    target_sources(app PRIVATE ${MX25L6433F_DIR}/mx25l6433f.c)

    if(DIAG  STREQUAL  Y)
        if(MX25L6433F_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MX25L6433F_DIAG)
            target_sources(app PRIVATE ${MX25L6433F_DIR}/mx25l6433f_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(MX25L6433F_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MX25L6433F_COMMANDS)
            target_sources(app PRIVATE ${MX25L6433F_DIR}/mx25l6433f_commands.c)
        endif()
    endif()
endif()
