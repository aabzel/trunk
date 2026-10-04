message(STATUS "GD5F1GQ5_MK_INC=${GD5F1GQ5_MK_INC}")
if( NOT (GD5F1GQ5_MK_INC  STREQUAL  Y))
    set(GD5F1GQ5_MK_INC Y)
    message(STATUS "+ GD5F1GQ5")

    set(GD5F1GQ5_DIR ${ROOT_DIR}/gd5f1gq5)
    message(STATUS "GD5F1GQ5_DIR=${GD5F1GQ5_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_GD5F1GQ5)
    target_compile_definitions(app PUBLIC HAS_GD5F1GQ5)
    target_compile_definitions(app PUBLIC HAS_GD5F1GQ5_PROC)

    target_include_directories(app PUBLIC ${GD5F1GQ5_DIR})
    target_sources(app PRIVATE ${GD5F1GQ5_DIR}/gd5f1gq5.c)

    if(DIAG  STREQUAL  Y)
        if(GD5F1GQ5_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GD5F1GQ5_DIAG)
            target_sources(app PRIVATE ${GD5F1GQ5_DIR}/gd5f1gq5_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(GD5F1GQ5_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GD5F1GQ5_COMMANDS)
            target_sources(app PRIVATE ${GD5F1GQ5_DIR}/gd5f1gq5_commands.c)
        endif()
    endif()
endif()
