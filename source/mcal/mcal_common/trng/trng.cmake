message(STATUS "TRNG_MK_INC=${TRNG_MK_INC}")
if( NOT (TRNG_MK_INC  STREQUAL  Y))
    set(TRNG_MK_INC Y)
    message(STATUS "+ TRNG")

    set(TRNG_DIR ${ROOT_DIR}/trng)
    message(STATUS "TRNG_DIR=${TRNG_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_TRNG)
    target_compile_definitions(app PUBLIC HAS_TRNG)
    target_compile_definitions(app PUBLIC HAS_TRNG_PROC)

    target_include_directories(app PUBLIC ${TRNG_DIR})
    target_sources(app PRIVATE ${TRNG_DIR}/trng.c)

    if(DIAG  STREQUAL  Y)
        if(TRNG_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_TRNG_DIAG)
            target_sources(app PRIVATE ${TRNG_DIR}/trng_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(TRNG_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_TRNG_COMMANDS)
            target_sources(app PRIVATE ${TRNG_DIR}/trng_commands.c)
        endif()
    endif()
endif()
