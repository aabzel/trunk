
message(STATUS "CLI_MK_INC=${CLI_MK_INC}")
if( NOT (CLI_MK_INC STREQUAL Y))
    set(CLI_MK_INC Y)
    message(STATUS "+ CLI as a protocol")

    set(CLI_DIR ${PROTOCOLS_DIR}/cli_drv)
    message(STATUS "CLI_DIR=${CLI_DIR}")

    add_compile_definitions(HAS_CLI)
    target_compile_definitions(app PUBLIC HAS_CLI)

    include_directories(${CLI_DIR})
    target_include_directories(app PUBLIC ${CLI_DIR})

    #Source code
    target_sources(app PRIVATE ${CLI_DIR}/cli_drv.c)
    target_sources(app PRIVATE ${CLI_DIR}/cli_general_config.c)
    target_sources(app PRIVATE ${CLI_DIR}/string_reader.c)

    if (TEST_FIRMWARE_COMMANDS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TEST_FIRMWARE_COMMANDS)
    endif()

    if (CLI_CMD_HISTORY STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_CLI_CMD_HISTORY)
    endif()

    if (CLI  STREQUAL  Y)
        if (CLI_NATIVE_COMMANDS STREQUAL Y)
             message(STATUS "+ CLI native commands")
             target_compile_definitions(app PUBLIC HAS_CLI_NATIVE_COMMANDS)
             target_sources(app PRIVATE ${CLI_DIR}/cli_native_commands.c)
        endif()
    endif()
endif()
