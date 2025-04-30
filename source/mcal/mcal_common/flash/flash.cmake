
message(STATUS "FLASH_MCAL_MK_INC=${FLASH_MCAL_MK_INC}")

if( NOT (FLASH_MCAL_MK_INC STREQUAL Y))
    set(FLASH_MCAL_MK_INC Y)

    message(STATUS "+FLASH DRV")

    set(FLASH_MCAL_DIR ${MCAL_COMMON_DIR}/flash)
    #@echo ${error FLASH_MCAL_DIR=${FLASH_MCAL_DIR))

    target_include_directories(app PUBLIC ${FLASH_MCAL_DIR})

    target_compile_definitions(app PUBLIC HAS_FLASH)

    target_sources(app PRIVATE ${FLASH_MCAL_DIR}/flash_general_drv.c)

    set(CRC16 Y)
    target_compile_definitions(app PUBLIC HAS_CRC16)

    if (FLASH_EX STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_FLASH_EX)
    endif()

    if (FLASH_WRITE STREQUAL Y)
        #@echo ${error FLASH_WRITE=${FLASH_WRITE))
        target_compile_definitions(app PUBLIC HAS_FLASH_WRITE)
    endif()

    if (DIAG STREQUAL Y)
        if (FLASH_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_FLASH_DIAG)
            target_sources(app PRIVATE ${FLASH_MCAL_DIR}/flash_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        #@echo ${error CLI=${CLI))
        if (FLASH_COMMANDS STREQUAL Y)
            #@echo ${error FLASH_COMMANDS=${FLASH_COMMANDS))
            target_compile_definitions(app PUBLIC HAS_FLASH_COMMANDS)
            target_sources(app PRIVATE ${FLASH_MCAL_DIR}/flash_commands.c)
        endif()
    endif()
endif()


