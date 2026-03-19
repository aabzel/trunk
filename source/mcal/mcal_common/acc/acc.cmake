message(STATUS "ACC_MK_INC=${ACC_MK_INC}")
if( NOT (ACC_MK_INC  STREQUAL  Y))
    set(ACC_MK_INC Y)
    message(STATUS "+ ACC")

    set(ACC_DIR ${ROOT_DIR}/acc)
    message(STATUS "ACC_DIR=${ACC_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_ACC)
    target_compile_definitions(app PUBLIC HAS_ACC)
    target_compile_definitions(app PUBLIC HAS_ACC_PROC)

    target_include_directories(app PUBLIC ${ACC_DIR})
    target_sources(app PRIVATE ${ACC_DIR}/acc.c)

    if(DIAG  STREQUAL  Y)
        if(ACC_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_ACC_DIAG)
            target_sources(app PRIVATE ${ACC_DIR}/acc_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(ACC_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_ACC_COMMANDS)
            target_sources(app PRIVATE ${ACC_DIR}/acc_commands.c)
        endif()
    endif()
endif()
