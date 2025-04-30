if( NOT (DS_TWR_MK_INC STREQUAL Y))
    set(DS_TWR_MK_INC Y)

    set(DS_TWR_DIR ${PROTOCOLS_DIR}/ds_twr)

    message(STATUS "+ DWM1000 Range")

    target_include_directories(app PUBLIC ${DS_TWR_DIR})

    target_compile_definitions(app PUBLIC HAS_DS_TWR)
    target_compile_definitions(app PUBLIC HAS_DS_TWR_PROC)

    target_sources(app PRIVATE ${DS_TWR_DIR}/ds_twr.c)
    target_sources(app PRIVATE ${DS_TWR_DIR}/ds_twr_responder.c)
    target_sources(app PRIVATE ${DS_TWR_DIR}/ds_twr_initiator.c)

    if (DIAG STREQUAL Y)
        if (DS_TWR_DIAG STREQUAL Y)
            message(STATUS "+ DS_TWR_DIAG")
            target_compile_definitions(app PUBLIC HAS_DS_TWR_DIAG)
            target_sources(app PRIVATE ${DS_TWR_DIR}/ds_twr_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (DS_TWR_COMMANDS STREQUAL Y)
            message(STATUS "+ DS_TWR_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_DS_TWR_COMMANDS)
            target_sources(app PRIVATE ${DS_TWR_DIR}/ds_twr_commands.c)
        endif()
    endif()
endif()
