message(STATUS "M_SEQ_MK_INC=${M_SEQ_MK_INC}")
if( NOT (M_SEQ_MK_INC  STREQUAL  Y))
    set(M_SEQ_MK_INC Y)
    message(STATUS "+ M_SEQ")

    set(M_SEQ_DIR ${ROOT_DIR}/m_seq)
    message(STATUS "M_SEQ_DIR=${M_SEQ_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_M_SEQ)
    target_compile_definitions(app PUBLIC HAS_M_SEQ)
    target_compile_definitions(app PUBLIC HAS_M_SEQ_PROC)

    target_include_directories(app PUBLIC ${M_SEQ_DIR})
    target_sources(app PRIVATE ${M_SEQ_DIR}/m_seq.c)

    if(DIAG  STREQUAL  Y)
        if(M_SEQ_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_M_SEQ_DIAG)
            target_sources(app PRIVATE ${M_SEQ_DIR}/m_seq_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(M_SEQ_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_M_SEQ_COMMANDS)
            target_sources(app PRIVATE ${M_SEQ_DIR}/m_seq_commands.c)
        endif()
    endif()
endif()
