message(STATUS "BIT_FIFO_MK_INC=${BIT_FIFO_MK_INC}")
if( NOT (BIT_FIFO_MK_INC  STREQUAL  Y))
    set(BIT_FIFO_MK_INC Y)
    message(STATUS "+ BIT_FIFO")

    set(BIT_FIFO_DIR ${ROOT_DIR}/bit_fifo)
    message(STATUS "BIT_FIFO_DIR=${BIT_FIFO_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_BIT_FIFO)
    target_compile_definitions(app PUBLIC HAS_BIT_FIFO)
    target_compile_definitions(app PUBLIC HAS_BIT_FIFO_PROC)

    target_include_directories(app PUBLIC ${BIT_FIFO_DIR})
    target_sources(app PRIVATE ${BIT_FIFO_DIR}/bit_fifo.c)

    if(DIAG  STREQUAL  Y)
        if(BIT_FIFO_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BIT_FIFO_DIAG)
            target_sources(app PRIVATE ${BIT_FIFO_DIR}/bit_fifo_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(BIT_FIFO_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BIT_FIFO_COMMANDS)
            target_sources(app PRIVATE ${BIT_FIFO_DIR}/bit_fifo_commands.c)
        endif()
    endif()
endif()
