message(STATUS "BPSK_MK_INC=${BPSK_MK_INC}")
if( NOT (BPSK_MK_INC  STREQUAL  Y))
    set(BPSK_MK_INC Y)

    set(BPSK_DIR ${COMPUTING_DIR}/bpsk)
    target_include_directories(app PUBLIC ${BPSK_DIR})

    target_compile_definitions(app PUBLIC HAS_BPSK)
    target_sources(app PRIVATE ${BPSK_DIR}/bpsk.c)

    if(DIAG  STREQUAL  Y)
        target_sources(app PRIVATE ${BPSK_DIR}/bpsk_diag.c)
    endif()
endif()
