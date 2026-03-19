
message(STATUS "MAILBOX_GENERAL_MK_INC=${MAILBOX_GENERAL_MK_INC}")
if( NOT (Y STREQUAL MAILBOX_GENERAL_MK_INC))
    set(MAILBOX_GENERAL_MK_INC Y)
    message(STATUS "+ MAILBOX General")

    set(MAILBOX_GENERAL_DIR ${MCAL_COMMON_DIR}/mailbox)
    message(STATUS "MAILBOX_GENERAL_DIR=${MAILBOX_GENERAL_DIR}")

    add_compile_definitions(HAS_MAILBOX)
    target_compile_definitions(app PUBLIC HAS_MAILBOX)

    include_directories(${MAILBOX_GENERAL_DIR})
    target_include_directories(app PUBLIC ${MAILBOX_GENERAL_DIR})

    target_sources(app PRIVATE ${MAILBOX_GENERAL_DIR}/mailbox_general.c)
    target_sources(app PRIVATE ${MAILBOX_GENERAL_DIR}/mailbox_isr.c)

    if(DIAG STREQUAL Y)
        if(MAILBOX_DIAG STREQUAL Y)
            message(STATUS "+ MAILBOX diag")
            target_compile_definitions(app PUBLIC HAS_MAILBOX_DIAG)
            target_sources(app PRIVATE ${MAILBOX_GENERAL_DIR}/mailbox_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(MAILBOX_COMMANDS STREQUAL Y)
            message(STATUS "+ MAILBOX commands")
            target_compile_definitions(app PUBLIC HAS_MAILBOX_COMMANDS)
            target_sources(app PRIVATE ${MAILBOX_GENERAL_DIR}/mailbox_commands.c)
        endif()
    endif()
endif()
