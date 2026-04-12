message(STATUS "HASH_TABLE_MK_INC=${HASH_TABLE_MK_INC}")
if( NOT (HASH_TABLE_MK_INC  STREQUAL  Y))
    set(HASH_TABLE_MK_INC Y)
    message(STATUS "+ HASH_TABLE")

    set(HASH_TABLE_DIR ${ROOT_DIR}/hash_table)
    message(STATUS "HASH_TABLE_DIR=${HASH_TABLE_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_HASH_TABLE)
    target_compile_definitions(app PUBLIC HAS_HASH_TABLE)
    target_compile_definitions(app PUBLIC HAS_HASH_TABLE_PROC)

    target_include_directories(app PUBLIC ${HASH_TABLE_DIR})
    target_sources(app PRIVATE ${HASH_TABLE_DIR}/hash_table.c)

    if(DIAG  STREQUAL  Y)
        if(HASH_TABLE_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_HASH_TABLE_DIAG)
            target_sources(app PRIVATE ${HASH_TABLE_DIR}/hash_table_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(HASH_TABLE_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_HASH_TABLE_COMMANDS)
            target_sources(app PRIVATE ${HASH_TABLE_DIR}/hash_table_commands.c)
        endif()
    endif()
endif()
