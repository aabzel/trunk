message(STATUS "SI4703_MK_INC=${SI4703_MK_INC}")
if( NOT (SI4703_MK_INC  STREQUAL  Y))
    set(SI4703_MK_INC Y)
    message(STATUS "+ SI4703")

    set(SI4703_DIR ${ROOT_DIR}/si4703)
    message(STATUS "SI4703_DIR=${SI4703_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SI4703)
    target_compile_definitions(app PUBLIC HAS_SI4703)
    target_compile_definitions(app PUBLIC HAS_SI4703_PROC)

    target_include_directories(app PUBLIC ${SI4703_DIR})
    target_sources(app PRIVATE ${SI4703_DIR}/si4703.c)

    if(DIAG  STREQUAL  Y)
        if(SI4703_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SI4703_DIAG)
            target_sources(app PRIVATE ${SI4703_DIR}/si4703_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SI4703_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SI4703_COMMANDS)
            target_sources(app PRIVATE ${SI4703_DIR}/si4703_commands.c)
        endif()
    endif()
endif()
