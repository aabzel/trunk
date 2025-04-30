message(STATUS "HEX_BIN_MK_INC=${HEX_BIN_MK_INC}")
if( NOT (HEX_BIN_MK_INC STREQUAL Y))

    set(HEX_BIN_MK_INC Y)
    message(STATUS "+HEX_BIN")

    set(HEX_BIN_DIR ${STORAGE_DIR}/hex_bin)
    message(STATUS "HEX_BIN_DIR=${HEX_BIN_DIR}")

    #@ echo ${error HEX_BIN_DIR = ${HEX_BIN_DIR))

    target_compile_definitions(app PUBLIC HAS_HEX_BIN)

    target_include_directories(app PUBLIC ${HEX_BIN_DIR})

    target_sources(app PRIVATE ${HEX_BIN_DIR}/hex_bin.c)

    if (DIAG STREQUAL Y)
        if (HEX_BIN_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_HEX_BIN_DIAG)
            target_sources(app PRIVATE ${HEX_BIN_DIR}/hex_bin_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (HEX_BIN_COMMANDS STREQUAL Y)
             target_compile_definitions(app PUBLIC HAS_HEX_BIN_COMMANDS)
            target_sources(app PRIVATE ${HEX_BIN_DIR}/hex_bin_commands.c)
        endif()
    endif()
endif()


