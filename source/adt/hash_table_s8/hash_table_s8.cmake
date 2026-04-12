message(STATUS "HASH_TABLE_S8_MK_INC=${HASH_TABLE_S8_MK_INC}")
if( NOT (HASH_TABLE_S8_MK_INC  STREQUAL  Y))
    set(HASH_TABLE_S8_MK_INC Y)
    message(STATUS "+ HASH_TABLE_S8")

    set(HASH_TABLE_S8_DIR ${ROOT_DIR}/hash_table_s8)
    message(STATUS "HASH_TABLE_S8_DIR=${HASH_TABLE_S8_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_HASH_TABLE_S8)
    target_compile_definitions(app PUBLIC HAS_HASH_TABLE_S8)
    target_compile_definitions(app PUBLIC HAS_HASH_TABLE_S8_PROC)

    target_include_directories(app PUBLIC ${HASH_TABLE_S8_DIR})
    target_sources(app PRIVATE ${HASH_TABLE_S8_DIR}/hash_table_s8.c)

    if(DIAG  STREQUAL  Y)
        if(HASH_TABLE_S8_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_HASH_TABLE_S8_DIAG)
            target_sources(app PRIVATE ${HASH_TABLE_S8_DIR}/hash_table_s8_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(HASH_TABLE_S8_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_HASH_TABLE_S8_COMMANDS)
            target_sources(app PRIVATE ${HASH_TABLE_S8_DIR}/hash_table_s8_commands.c)
        endif()
    endif()
endif()
