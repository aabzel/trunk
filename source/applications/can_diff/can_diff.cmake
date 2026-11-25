message(STATUS "CAN_DIFF_MK_INC=${CAN_DIFF_MK_INC}")
if( NOT (CAN_DIFF_MK_INC  STREQUAL  Y))
    set(CAN_DIFF_MK_INC Y)
    message(STATUS "+ CAN_DIFF")

    set(CAN_DIFF_DIR ${ROOT_DIR}/can_diff)
    message(STATUS "CAN_DIFF_DIR=${CAN_DIFF_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_CAN_DIFF)
    target_compile_definitions(app PUBLIC HAS_CAN_DIFF)
    target_compile_definitions(app PUBLIC HAS_CAN_DIFF_PROC)

    target_include_directories(app PUBLIC ${CAN_DIFF_DIR})
    target_sources(app PRIVATE ${CAN_DIFF_DIR}/can_diff.c)

    if(DIAG  STREQUAL  Y)
        if(CAN_DIFF_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_DIFF_DIAG)
            target_sources(app PRIVATE ${CAN_DIFF_DIR}/can_diff_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(CAN_DIFF_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_DIFF_COMMANDS)
            target_sources(app PRIVATE ${CAN_DIFF_DIR}/can_diff_commands.c)
        endif()
    endif()
endif()
