message(STATUS "CAN_CAT_MK_INC=${CAN_CAT_MK_INC}")
if( NOT (CAN_CAT_MK_INC  STREQUAL  Y))
    set(CAN_CAT_MK_INC Y)
    message(STATUS "+ CAN_CAT")

    set(CAN_CAT_DIR ${ROOT_DIR}/can_cat)
    message(STATUS "CAN_CAT_DIR=${CAN_CAT_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_CAN_CAT)
    target_compile_definitions(app PUBLIC HAS_CAN_CAT)
    target_compile_definitions(app PUBLIC HAS_CAN_CAT_PROC)

    target_include_directories(app PUBLIC ${CAN_CAT_DIR})
    target_sources(app PRIVATE ${CAN_CAT_DIR}/can_cat.c)

    if(DIAG  STREQUAL  Y)
        if(CAN_CAT_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_CAT_DIAG)
            target_sources(app PRIVATE ${CAN_CAT_DIR}/can_cat_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(CAN_CAT_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_CAN_CAT_COMMANDS)
            target_sources(app PRIVATE ${CAN_CAT_DIR}/can_cat_commands.c)
        endif()
    endif()
endif()
