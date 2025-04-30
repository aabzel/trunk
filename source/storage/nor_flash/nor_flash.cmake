message(STATUS "NOR_FLASH_MK_INC=${NOR_FLASH_MK_INC}")
if( NOT (NOR_FLASH_MK_INC  STREQUAL Y))
    set(NOR_FLASH_MK_INC Y)
    message(STATUS "+ Mx25r6435f")

    set(NOR_FLASH_DIR ${STORAGE_DIR}/nor_flash)
    message(STATUS "NOR_FLASH_DIR=${NOR_FLASH_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_NOR_FLASH)
    target_compile_definitions(app PUBLIC HAS_NOR_FLASH)

    target_include_directories(app PUBLIC ${NOR_FLASH_DIR})
    target_sources(app PRIVATE ${NOR_FLASH_DIR}/nor_flash_drv.c)

    if(DIAG  STREQUAL Y)
        if(NOR_FLASH_DIAG  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NOR_FLASH_DIAG)
            target_sources(app PRIVATE ${NOR_FLASH_DIR}/nor_flash_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL Y)
        if(NOR_FLASH_COMMANDS  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NOR_FLASH_COMMANDS)
            target_sources(app PRIVATE ${NOR_FLASH_DIR}/nor_flash_commands.c)
        endif()
    endif()
endif()
