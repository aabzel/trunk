message(STATUS "FLASH_CUSTOM_CMAKE_INC=${FLASH_CUSTOM_CMAKE_INC}")
if( NOT (FLASH_CUSTOM_CMAKE_INC STREQUAL Y))
    set(FLASH_CUSTOM_CMAKE_INC Y)
    message(STATUS "FLASH_CUSTOM_CMAKE_INC=${FLASH_CUSTOM_CMAKE_INC}")
    message(STATUS "+ FLASH for Zephyr")

    set(FLASH_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/flash)
    message(STATUS "FLASH_ZEPHYR_DIR=${FLASH_ZEPHYR_DIR}")

    #add_compile_definitions(HAS_FLASH)
    target_compile_definitions(app PUBLIC HAS_FLASH)
    target_compile_definitions(app PUBLIC HAS_FLASH_CUSTOM)

    #include_directories(${FLASH_ZEPHYR_DIR})
    target_include_directories(app PUBLIC ${FLASH_ZEPHYR_DIR})
    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/zephyr/include/zephyr/drivers)

    target_sources(app PRIVATE ${FLASH_ZEPHYR_DIR}/flash_drv.c)

    if(FLASH_DIAG STREQUAL Y)
        message(STATUS "+ FLASH_DIAG custom ")
        target_sources(app PRIVATE ${FLASH_ZEPHYR_DIR}/flash_custom_diag.c)
    endif()
    
    if(CLI STREQUAL Y)
        if(FLASH_COMMANDS STREQUAL Y)
            message(STATUS "+ FLASH_COMMANDS")
            target_sources(app PRIVATE ${FLASH_ZEPHYR_DIR}/flash_custom_commands.c)
        endif()
    endif()

endif()



