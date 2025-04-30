message(STATUS "W25Q16BV_MK_INC=${W25Q16BV_MK_INC}")
if( NOT (W25Q16BV_MK_INC STREQUAL Y))
    set(W25Q16BV_MK_INC Y)
    message(STATUS "+ W25q16bv")

    set(W25Q16BV_DIR ${ASICS_DIR}/w25q16bv)
    message(STATUS "W25Q16BV_DIR=${W25Q16BV_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_W25Q16BV)
    target_compile_definitions(app PUBLIC HAS_W25Q16BV)

    target_include_directories(app PUBLIC ${W25Q16BV_DIR})
    target_sources(app PRIVATE ${W25Q16BV_DIR}/w25q16bv_drv.c)

    if(DIAG STREQUAL Y)
        if(W25Q16BV_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_W25Q16BV_DIAG)
            target_sources(app PRIVATE ${W25Q16BV_DIR}/w25q16bv_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(W25Q16BV_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_W25Q16BV_COMMANDS)
            target_sources(app PRIVATE ${W25Q16BV_DIR}/w25q16bv_commands.c)
        endif()
    endif()
endif()
