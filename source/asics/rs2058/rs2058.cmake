message(STATUS "RS2058_MK_INC=${RS2058_MK_INC}")
if( NOT (RS2058_MK_INC STREQUAL Y))
    set(RS2058_MK_INC Y)
    message(STATUS "+ RS2058")

    set(RS2058_DIR ${ASICS_DIR}/rs2058)
    message(STATUS "RS2058_DIR=${RS2058_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_RS2058)
    target_compile_definitions(app PUBLIC HAS_RS2058)

    target_include_directories(app PUBLIC ${RS2058_DIR})
    target_sources(app PRIVATE ${RS2058_DIR}/rs2058_drv.c)

    if(DIAG STREQUAL Y)
        if(RS2058_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_RS2058_DIAG)
            target_sources(app PRIVATE ${RS2058_DIR}/rs2058_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(RS2058_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_RS2058_COMMANDS)
            target_sources(app PRIVATE ${RS2058_DIR}/rs2058_commands.c)
        endif()
    endif()
endif()
