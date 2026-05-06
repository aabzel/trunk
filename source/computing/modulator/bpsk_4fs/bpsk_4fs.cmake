message(STATUS "BPSK_4FS_MK_INC=${BPSK_4FS_MK_INC}")
if( NOT (BPSK_4FS_MK_INC  STREQUAL  Y))
    set(BPSK_4FS_MK_INC Y)

    set(BPSK_4FS_DIR ${COMPUTING_DIR}/bpsk_4fs)
    target_include_directories(app PUBLIC ${BPSK_4FS_DIR})

    target_compile_definitions(app PUBLIC HAS_BPSK_4FS)
    target_sources(app PRIVATE ${BPSK_4FS_DIR}/bpsk_4fs.c)

    if(DIAG  STREQUAL  Y)
        target_sources(app PRIVATE ${BPSK_4FS_DIR}/bpsk_4fs_diag.c)
    endif()
endif()
