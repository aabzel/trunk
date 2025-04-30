
message(STATUS "READER_MK_INC=${READER_MK_INC}")
if( NOT (READER_MK_INC STREQUAL Y))
    set(READER_MK_INC Y)
    message(STATUS "+ READER as a protocol")

    set(READER_DIR ${PROTOCOLS_DIR}/string_reader)
    message(STATUS "READER_DIR=${READER_DIR}")

    add_compile_definitions(HAS_READER)
    target_compile_definitions(app PUBLIC HAS_READER)

    include_directories(${READER_DIR})
    target_include_directories(app PUBLIC ${READER_DIR})

    #Source code
    target_sources(app PRIVATE ${READER_DIR}/string_reader.c)
    target_sources(app PRIVATE ${READER_DIR}/string_reader_general_config.c)
    target_sources(app PRIVATE ${READER_DIR}/string_reader.c)

    if (TEST_FIRMWARE_COMMANDS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TEST_FIRMWARE_COMMANDS)
    endif()

    if (READER_CMD_HISTORY STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_READER_CMD_HISTORY)
    endif()

    if (READER  STREQUAL  Y)
        if (READER_NATIVE_COMMANDS STREQUAL Y)
             message(STATUS "+ READER native commands")
             target_compile_definitions(app PUBLIC HAS_READER_NATIVE_COMMANDS)
             target_sources(app PRIVATE ${READER_DIR}/string_reader_native_commands.c)
        endif()
    endif()
endif()
