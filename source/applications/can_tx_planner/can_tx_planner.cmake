message(STATUS "CAN_TX_PLANNER_MK_INC=${CAN_TX_PLANNER_MK_INC}")
if( NOT (CAN_TX_PLANNER_MK_INC  STREQUAL  Y))
    set(CAN_TX_PLANNER_MK_INC Y)
    message(STATUS "+ CAN_TX_PLANNER")

    set(CAN_TX_PLANNER_DIR ${ROOT_DIR}/can_tx_planner)
    message(STATUS "CAN_TX_PLANNER_DIR=${CAN_TX_PLANNER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_CAN_TX_PLANNER)
    target_compile_definitions(app PUBLIC HAS_CAN_TX_PLANNER)
    target_compile_definitions(app PUBLIC HAS_CAN_TX_PLANNER_PROC)

    target_include_directories(app PUBLIC ${CAN_TX_PLANNER_DIR})
    target_sources(app PRIVATE ${CAN_TX_PLANNER_DIR}/can_tx_planner.c)

    if(DIAG  STREQUAL  Y)
        if(CAN_TX_PLANNER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_TX_PLANNER_DIAG)
            target_sources(app PRIVATE ${CAN_TX_PLANNER_DIR}/can_tx_planner_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(CAN_TX_PLANNER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_TX_PLANNER_COMMANDS)
            target_sources(app PRIVATE ${CAN_TX_PLANNER_DIR}/can_tx_planner_commands.c)
        endif()
    endif()
endif()
