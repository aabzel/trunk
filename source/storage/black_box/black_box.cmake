message(STATUS "BLACK_BOX_MK_INC=${BLACK_BOX_MK_INC}")
if( NOT (BLACK_BOX_MK_INC STREQUAL Y))
    set(BLACK_BOX_MK_INC Y)
    message(STATUS "+ BLACK_BOX")

    set(BLACK_BOX_DIR ${APPLICATIONS_DIR}/black_box)

    target_include_directories(app PUBLIC ${BLACK_BOX_DIR})

    target_compile_definitions(app PUBLIC HAS_BLACK_BOX)
    target_sources(app PRIVATE ${BLACK_BOX_DIR}/black_box.c)

    if(BT_BLE_UWB_TAG_CFG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BT_BLE_UWB_TAG_CFG)
    endif()

    if(BLE_SPEAKER_CFG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BLE_SPEAKER_CFG)
    endif()

    if(DIAG STREQUAL Y)
        if(BLACK_BOX_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_BLACK_BOX_DIAG)
            target_sources(app PRIVATE ${BLACK_BOX_DIR}/black_box_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(BLACK_BOX_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_BLACK_BOX_COMMANDS)
            target_sources(app PRIVATE ${BLACK_BOX_DIR}/black_box_commands.c)
        endif()
    endif()
endif()
