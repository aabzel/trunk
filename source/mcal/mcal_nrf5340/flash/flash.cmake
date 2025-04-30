
message(STATUS "NRFX_FLASH_DRV_MK_INC=${NRFX_FLASH_DRV_MK_INC}")
if( NOT (NRFX_FLASH_DRV_MK_INC STREQUAL Y))
    set(NRFX_FLASH_DRV_MK_INC Y)

    set(NRFX_FLASH_DIR ${MCAL_NRF5340_DIR}/flash)
    message(STATUS " + FLASH_CUSTOM")

    target_include_directories(app PUBLIC ${NRFX_FLASH_DIR})

    target_compile_definitions(app PUBLIC HAS_FLASH)
    target_compile_definitions(app PUBLIC HAS_FLASH_CUSTOM)
    target_compile_definitions(app PUBLIC HAS_ON_CHIP_FLASH)

    target_sources(app PRIVATE ${NRFX_FLASH_DIR}/flash_drv.c)

    set(CRC16 Y)
    target_compile_definitions(app PUBLIC HAS_CRC16)

    if (FLASH_EX STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_FLASH_EX)
    endif()

    if (FLASH_WRITE STREQUAL Y)
        message(STATUS " + FLASH_WRITE")
        #@echo ${error FLASH_WRITE=${FLASH_WRITE))
        target_compile_definitions(app PUBLIC HAS_FLASH_WRITE)
    endif()

    if (DIAG STREQUAL Y)
        if (FLASH_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_FLASH_DIAG)
            target_sources(app PRIVATE ${NRFX_FLASH_DIR}/flash_custom_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (FLASH_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_FLASH_COMMANDS)
            target_sources(app PRIVATE ${NRFX_FLASH_DIR}/flash_custom_commands.c)
        endif()
    endif()
endif()

