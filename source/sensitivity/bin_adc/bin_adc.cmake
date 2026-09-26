message(STATUS "BIN_ADC_MK_INC=${BIN_ADC_MK_INC}")
if( NOT (BIN_ADC_MK_INC  STREQUAL  Y))
    set(BIN_ADC_MK_INC Y)
    message(STATUS "+ BIN_ADC")

    set(BIN_ADC_DIR ${ROOT_DIR}/bin_adc)
    message(STATUS "BIN_ADC_DIR=${BIN_ADC_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_BIN_ADC)
    target_compile_definitions(app PUBLIC HAS_BIN_ADC)
    target_compile_definitions(app PUBLIC HAS_BIN_ADC_PROC)

    target_include_directories(app PUBLIC ${BIN_ADC_DIR})
    target_sources(app PRIVATE ${BIN_ADC_DIR}/bin_adc.c)

    if(DIAG  STREQUAL  Y)
        if(BIN_ADC_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BIN_ADC_DIAG)
            target_sources(app PRIVATE ${BIN_ADC_DIR}/bin_adc_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(BIN_ADC_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BIN_ADC_COMMANDS)
            target_sources(app PRIVATE ${BIN_ADC_DIR}/bin_adc_commands.c)
        endif()
    endif()
endif()
