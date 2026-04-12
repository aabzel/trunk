if(NOT FLASH_DRV_MK_INC)
    set(FLASH_DRV_MK_INC Y)

    set(FLASH_DIR ${MCAL_CUSTOM_DIR}/flash)

    include_directories(${FLASH_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_FLASH_CUSTOM")

    string(APPEND SOURCES_C " ${FLASH_DIR}/flash_mcal.c")

    set(CRC16 Y)
    string(APPEND MCAL_OPT " -DHAS_CRC16")

    if(FLASH_EX STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_FLASH_EX")
    endif()

    if(FLASH_WRITE STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_FLASH_WRITE")
    endif()

    if(DIAG STREQUAL Y)
        if(FLASH_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_FLASH_DIAG")
            string(APPEND SOURCES_C " ${FLASH_DIR}/flash_custom_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(FLASH_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_FLASH_COMMANDS")
            string(APPEND SOURCES_C " ${FLASH_DIR}/flash_custom_commands.c")
        endif()
    endif()

endif()