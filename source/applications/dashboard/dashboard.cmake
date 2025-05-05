message(STATUS "DASHBOARD_MK_INC=${DASHBOARD_MK_INC}")
if( NOT (DASHBOARD_MK_INC STREQUAL Y))
    set(DASHBOARD_MK_INC Y)
    message(STATUS "+ DASHBOARD")

    set(DASHBOARD_DIR ${APPLICATIONS_DIR}/dashboard)

    target_include_directories(app PUBLIC ${DASHBOARD_DIR})

    target_compile_definitions(app PUBLIC HAS_DASHBOARD)
    target_sources(app PRIVATE ${DASHBOARD_DIR}/dashboard.c)


    if(BT_BLE_UWB_TAG_CFG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BT_BLE_UWB_TAG_CFG)
    endif()

    if(BLE_SPEAKER_CFG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BLE_SPEAKER_CFG)
    endif()

    if(DIAG STREQUAL Y)
        if(DASHBOARD_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_DASHBOARD_DIAG)
            target_sources(app PRIVATE ${DASHBOARD_DIR}/dashboard_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(DASHBOARD_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_DASHBOARD_COMMANDS)
            target_sources(app PRIVATE ${DASHBOARD_DIR}/dashboard_commands.c)
        endif()
    endif()
endif()
