
message(STATUS "CAN_MK_INC=${CAN_MK_INC}")
if( NOT (CAN_MK_INC STREQUAL Y))
    set(CAN_MK_INC Y)
    message(STATUS "+ CAN General")

    set(CAN_GENERAL_DIR ${MCAL_COMMON_DIR}/can)
    message(STATUS "CAN_GENERAL_DIR=${CAN_GENERAL_DIR}")

    add_compile_definitions(HAS_CAN)
    target_compile_definitions(app PUBLIC HAS_CAN)

    target_include_directories(app PUBLIC ${CAN_GENERAL_DIR})

    target_sources(app PRIVATE ${CAN_GENERAL_DIR}/can_general.c)

    if(DIAG STREQUAL Y)
        if(CAN_DIAG STREQUAL Y)
            target_sources(app PRIVATE ${CAN_GENERAL_DIR}/can_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(CAN_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_CAN_COMMANDS)
            target_sources(app PRIVATE ${CAN_GENERAL_DIR}/can_commands.c)
        endif()
    endif()
endif()

