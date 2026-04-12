
if(NOT (MATH_MK_INC STREQUAL Y))
    set(MATH_MK_INC Y )

    set(MATH_DIR "${COMPUTING_DIR}/math")
    include_directories(${MATH_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_MATH")
    string(APPEND SOURCES_C " ${MATH_DIR}/utils_math.c")

    if(DIAG STREQUAL Y)
        string(APPEND SOURCES_C " ${MATH_DIR}/math_diag.c")
    endif()

    if(MATH_VECTOR STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_MATH_VECTOR")
        string(APPEND MCAL_OPT " -DHAS_VECTOR_MATH")
        string(APPEND SOURCES_C " ${MATH_DIR}/vector_math.c")
    endif()

    if(MATH_VECTOR_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_MATH_VECTOR_DIAG")
        string(APPEND SOURCES_C " ${MATH_DIR}/vector_diag.c")
    endif()

    if(MATH_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_MATH_COMMANDS")
        string(APPEND SOURCES_C " ${MATH_DIR}/math_commands.c")
    endif()
endif()