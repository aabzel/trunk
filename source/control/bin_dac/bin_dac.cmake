message(STATUS "BIN_DAC_MK_INC=${BIN_DAC_MK_INC}")
if( NOT (BIN_DAC_MK_INC  STREQUAL  Y))
    set(BIN_DAC_MK_INC Y)
    message(STATUS "+ BIN_DAC")

    set(BIN_DAC_DIR ${ROOT_DIR}/bin_dac)
    message(STATUS "BIN_DAC_DIR=${BIN_DAC_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_BIN_DAC)
    target_compile_definitions(app PUBLIC HAS_BIN_DAC)
    target_compile_definitions(app PUBLIC HAS_BIN_DAC_PROC)

    target_include_directories(app PUBLIC ${BIN_DAC_DIR})
    target_sources(app PRIVATE ${BIN_DAC_DIR}/bin_dac.c)

    if(DIAG  STREQUAL  Y)
        if(BIN_DAC_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BIN_DAC_DIAG)
            target_sources(app PRIVATE ${BIN_DAC_DIR}/bin_dac_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(BIN_DAC_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BIN_DAC_COMMANDS)
            target_sources(app PRIVATE ${BIN_DAC_DIR}/bin_dac_commands.c)
        endif()
    endif()
endif()
