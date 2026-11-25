message(STATUS "CAN_RX_HIST_MK_INC=${CAN_RX_HIST_MK_INC}")
if( NOT (CAN_RX_HIST_MK_INC  STREQUAL  Y))
    set(CAN_RX_HIST_MK_INC Y)
    message(STATUS "+ CAN_RX_HIST")

    set(CAN_RX_HIST_DIR ${ROOT_DIR}/can_rx_hist)
    message(STATUS "CAN_RX_HIST_DIR=${CAN_RX_HIST_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_CAN_RX_HIST)
    target_compile_definitions(app PUBLIC HAS_CAN_RX_HIST)
    target_compile_definitions(app PUBLIC HAS_CAN_RX_HIST_PROC)

    target_include_directories(app PUBLIC ${CAN_RX_HIST_DIR})
    target_sources(app PRIVATE ${CAN_RX_HIST_DIR}/can_rx_hist.c)

    if(DIAG  STREQUAL  Y)
        if(CAN_RX_HIST_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_RX_HIST_DIAG)
            target_sources(app PRIVATE ${CAN_RX_HIST_DIR}/can_rx_hist_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(CAN_RX_HIST_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_RX_HIST_COMMANDS)
            target_sources(app PRIVATE ${CAN_RX_HIST_DIR}/can_rx_hist_commands.c)
        endif()
    endif()
endif()
