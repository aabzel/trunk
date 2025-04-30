
if( NOT (NRF5340_MK_INC STREQUAL Y))
    set(NRF5340_MK_INC Y)

    set(NRF5340_DIR ${MICROCONTROLLER_DIR}/nRF5340)
    message(STATUS "NRF5340_DIR=${NRF5340_DIR}")

    message(STATUS "+ nRF5340")

    #add_compile_definitions(NRF5340_XXAA)
    target_compile_definitions(app PUBLIC NRF5340_XXAA)
    target_compile_definitions(app PUBLIC HAS_ARM)
    target_compile_definitions(app PUBLIC HAS_MULTICORE)
    target_compile_definitions(app PUBLIC HAS_NRF5340)

    include_directories(${NRF5340_DIR})

    target_sources(app PRIVATE ${NRF5340_DIR}/nrf5340.c)
    target_sources(app PRIVATE ${NRF5340_DIR}/pin_config.c)

    if (CLOCK STREQUAL Y)
        message(STATUS "+ CLOCK configs")
        target_sources(app PRIVATE ${NRF5340_DIR}/clock_config.c)
    endif()
    
    if (FLASH STREQUAL Y)
        message(STATUS "+ FLASH configs")
        target_sources(app PRIVATE ${NRF5340_DIR}/flash_config.c)
    endif()

    if (FLASH_FS STREQUAL Y)
        message(STATUS "+ FLASH_FS configs")
        target_sources(app PRIVATE ${NRF5340_DIR}/flash_fs_config.c)
    endif()

    if (NVS STREQUAL Y)
        message(STATUS "+ NVS configs")
        target_sources(app PRIVATE ${NRF5340_DIR}/nvs_config.c)
    endif()

    if (PARAM STREQUAL Y)
        message(STATUS "+ PARAM configs")
        target_sources(app PRIVATE ${NRF5340_DIR}/param_config.c)
    endif()
endif()