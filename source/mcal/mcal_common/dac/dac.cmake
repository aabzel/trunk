
message(STATUS "DAC_GENERAL_MK_INC=${DAC_GENERAL_MK_INC}")
if( NOT (Y STREQUAL DAC_GENERAL_MK_INC))
    set(DAC_GENERAL_MK_INC Y)
    message(STATUS "+ DAC General")

    set(DAC_GENERAL_DIR ${MCAL_COMMON_DIR}/dac)
    message(STATUS "DAC_GENERAL_DIR=${DAC_GENERAL_DIR}")

    add_compile_definitions(HAS_DAC)
    target_compile_definitions(app PUBLIC HAS_DAC)

    include_directories(${DAC_GENERAL_DIR})
    target_include_directories(app PUBLIC ${DAC_GENERAL_DIR})

    target_sources(app PRIVATE ${DAC_GENERAL_DIR}/dac_general.c)
    target_sources(app PRIVATE ${DAC_GENERAL_DIR}/dac_isr.c)

    if(DIAG STREQUAL Y)
        if(DAC_DIAG STREQUAL Y)
            message(STATUS "+ DAC diag")
            target_compile_definitions(app PUBLIC HAS_DAC_DIAG)
            target_sources(app PRIVATE ${DAC_GENERAL_DIR}/dac_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(DAC_COMMANDS STREQUAL Y)
            message(STATUS "+ DAC commands")
            target_compile_definitions(app PUBLIC HAS_DAC_COMMANDS)
            target_sources(app PRIVATE ${DAC_GENERAL_DIR}/dac_commands.c)
        endif()
    endif()
endif()
