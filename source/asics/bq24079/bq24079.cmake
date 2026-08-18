
message(STATUS "BQ24079_CMK_INC=${BQ24079_CMK_INC}")

if( NOT (BQ24079_CMK_INC STREQUAL Y))
    set(BQ24079_CMK_INC Y)

    set(BQ24079_DIR ${ASICS_DIR}/bq24079)
    message(STATUS "+ BQ24079 Bluetooth Module driver")

    target_include_directories(app PUBLIC ${BQ24079_DIR})

    target_compile_definitions(app PUBLIC HAS_BQ24079)
    target_compile_definitions(app PUBLIC HAS_BQ24079_PROC)

    target_sources(app PRIVATE ${BQ24079_DIR}/bq24079_drv.c)

    if (DIAG STREQUAL Y)
        if (BQ24079_DIAG STREQUAL Y)
            message(STATUS "+ BQ24079 diag")
            target_compile_definitions(app PUBLIC HAS_BQ24079_DIAG)
            target_sources(app PRIVATE ${BQ24079_DIR}/bq24079_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (BQ24079_COMMANDS STREQUAL Y)
            message(STATUS "+ BQ24079 commands")
            target_compile_definitions(app PUBLIC HAS_BQ24079_COMMANDS)
            target_sources(app PRIVATE ${BQ24079_DIR}/bq24079_commands.c)
        endif()
    endif()
endif()
