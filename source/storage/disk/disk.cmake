message(STATUS "DISK_MK_INC=${DISK_MK_INC}")
if( NOT (DISK_MK_INC  STREQUAL  Y))
    set(DISK_MK_INC Y)
    message(STATUS "+ DISK")

    set(DISK_DIR ${ROOT_DIR}/disk)
    message(STATUS "DISK_DIR=${DISK_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_DISK)
    target_compile_definitions(app PUBLIC HAS_DISK)
    target_compile_definitions(app PUBLIC HAS_DISK_PROC)

    target_include_directories(app PUBLIC ${DISK_DIR})
    target_sources(app PRIVATE ${DISK_DIR}/disk.c)

    if(DIAG  STREQUAL  Y)
        if(DISK_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DISK_DIAG)
            target_sources(app PRIVATE ${DISK_DIR}/disk_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(DISK_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DISK_COMMANDS)
            target_sources(app PRIVATE ${DISK_DIR}/disk_commands.c)
        endif()
    endif()
endif()
