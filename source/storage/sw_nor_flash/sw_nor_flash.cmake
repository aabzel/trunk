message(STATUS "SW_NOR_FLASH_MK_INC=${SW_NOR_FLASH_MK_INC}")
if( NOT (SW_NOR_FLASH_MK_INC  STREQUAL Y))
    set(SW_NOR_FLASH_MK_INC Y)
    message(STATUS "+ Mx25r6435f")

    set(SW_NOR_FLASH_DIR ${STORAGE_DIR}/sw_nor_flash)
    message(STATUS "SW_NOR_FLASH_DIR=${SW_NOR_FLASH_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_SW_NOR_FLASH)
    target_compile_definitions(app PUBLIC HAS_SW_NOR_FLASH)

    target_include_directories(app PUBLIC ${SW_NOR_FLASH_DIR})
    target_sources(app PRIVATE ${SW_NOR_FLASH_DIR}/sw_nor_flash_drv.c)

    if(DIAG  STREQUAL Y)
        if(SW_NOR_FLASH_DIAG  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SW_NOR_FLASH_DIAG)
            target_sources(app PRIVATE ${SW_NOR_FLASH_DIR}/sw_nor_flash_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL Y)
        if(SW_NOR_FLASH_COMMANDS  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SW_NOR_FLASH_COMMANDS)
            target_sources(app PRIVATE ${SW_NOR_FLASH_DIR}/sw_nor_flash_commands.c)
        endif()
    endif()
endif()
