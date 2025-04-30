message(STATUS "W25Q32JV_MK_INC=${W25Q32JV_MK_INC}")
if( NOT (W25Q32JV_MK_INC STREQUAL Y))
    set(W25Q32JV_MK_INC Y)
    message(STATUS "+ W25q32jv")

    set(W25Q32JV_DIR ${ASICS_DIR}/w25q32jv)
    message(STATUS "W25Q32JV_DIR=${W25Q32JV_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_W25Q32JV)
    target_compile_definitions(app PUBLIC HAS_W25Q32JV)

    target_include_directories(app PUBLIC ${W25Q32JV_DIR})
    target_sources(app PRIVATE ${W25Q32JV_DIR}/w25q32jv_drv.c)

    if(DIAG STREQUAL Y)
        if(W25Q32JV_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_W25Q32JV_DIAG)
            target_sources(app PRIVATE ${W25Q32JV_DIR}/w25q32jv_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(W25Q32JV_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_W25Q32JV_COMMANDS)
            target_sources(app PRIVATE ${W25Q32JV_DIR}/w25q32jv_commands.c)
        endif()
    endif()
endif()
