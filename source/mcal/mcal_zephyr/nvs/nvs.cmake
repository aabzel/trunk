
message(STATUS "ZEPHYR_NVS_DRV_MK_INC=${ZEPHYR_NVS_DRV_MK_INC}")
if( NOT (ZEPHYR_NVS_DRV_MK_INC STREQUAL Y))
    set(ZEPHYR_NVS_DRV_MK_INC Y)

    set(ZEPHYR_NVS_DIR ${MCAL_ZEPHYR_DIR}/nvs)
    message(STATUS " + NVS_CUSTOM")

    target_include_directories(app PUBLIC ${ZEPHYR_NVS_DIR})

    target_compile_definitions(app PUBLIC HAS_NVS)
    target_compile_definitions(app PUBLIC HAS_NVS_CUSTOM)

    target_sources(app PRIVATE ${ZEPHYR_NVS_DIR}/nvs_drv.c)

    if (NVS_WRITE STREQUAL Y)
        #@echo ${error NVS_WRITE=${NVS_WRITE))
        target_compile_definitions(app PUBLIC HAS_NVS_WRITE)
    endif()

    if (DIAG STREQUAL Y)
        if (NVS_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NVS_DIAG)
            target_sources(app PRIVATE ${ZEPHYR_NVS_DIR}/nvs_custom_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (NVS_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NVS_COMMANDS)
            target_sources(app PRIVATE ${ZEPHYR_NVS_DIR}/nvs_custom_commands.c)
        endif()
    endif()
endif()


