
if(NOT (CODE_GENERATOR_MK_INC STREQUAL Y))
    set(CODE_GENERATOR_MK_INC Y )
    set(MCAL_CODE_GENERATOR_DIR "${COMMON_DIR}/code_generator")

    include_directories( ${MCAL_CODE_GENERATOR_DIR})

    string(APPEND MCAL_OPT " -DHAS_CODE_GENERATOR")
endif()

