message(STATUS "FLASH_MCAL_MK_INC=${FLASH_MCAL_MK_INC}")
if( NOT (FLASH_MCAL_MK_INC STREQUAL Y))
    set(FLASH_MCAL_MK_INC Y)

    set(FLASH_MCAL_DIR "${MCAL_COMMON_DIR}/flash")
    include_directories(${FLASH_MCAL_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_FLASH")

    string(APPEND SOURCES_C " ${FLASH_MCAL_DIR}/flash_common.c")

    if(CRC16 STREQUAL N)
        message(WARNING "Add CRC16")
    endif()

    if(FLASH_EX STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_FLASH_EX")
    endif()

    if(FLASH_WRITE STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_FLASH_WRITE")
    endif()

    if(DIAG STREQUAL Y)
        if(FLASH_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_FLASH_DIAG")
            string(APPEND SOURCES_C " ${FLASH_MCAL_DIR}/flash_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(FLASH_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_FLASH_COMMANDS")
            string(APPEND SOURCES_C " ${FLASH_MCAL_DIR}/flash_commands.c")
        endif()
    endif()
endif()

