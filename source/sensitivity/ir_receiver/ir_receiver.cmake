message(STATUS "IR_RECEIVER_MK_INC=${IR_RECEIVER_MK_INC}")
if( NOT (IR_RECEIVER_MK_INC  STREQUAL  Y))
    set(IR_RECEIVER_MK_INC Y)
    message(STATUS "+ IR_RECEIVER")

    set(IR_RECEIVER_DIR ${ROOT_DIR}/ir_receiver)
    message(STATUS "IR_RECEIVER_DIR=${IR_RECEIVER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_IR_RECEIVER)
    target_compile_definitions(app PUBLIC HAS_IR_RECEIVER)
    target_compile_definitions(app PUBLIC HAS_IR_RECEIVER_PROC)

    target_include_directories(app PUBLIC ${IR_RECEIVER_DIR})
    target_sources(app PRIVATE ${IR_RECEIVER_DIR}/ir_receiver.c)

    if(DIAG  STREQUAL  Y)
        if(IR_RECEIVER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_IR_RECEIVER_DIAG)
            target_sources(app PRIVATE ${IR_RECEIVER_DIR}/ir_receiver_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(IR_RECEIVER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_IR_RECEIVER_COMMANDS)
            target_sources(app PRIVATE ${IR_RECEIVER_DIR}/ir_receiver_commands.c)
        endif()
    endif()
endif()
