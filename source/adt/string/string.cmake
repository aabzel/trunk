
message(STATUS "STRING_MK_INC=${STRING_MK_INC}")
if( NOT (STRING_MK_INC STREQUAL Y))
    set(STRING_MK_INC Y)
    message(STATUS "Link String Processor")

    set(STRING_DIR ${COMPUTING_DIR}/string)
    message(STATUS "STRING_DIR=${STRING_DIR}")
    
    message(STATUS "STR2_DOUBLE=[${STR2_DOUBLE}]")
    message(STATUS "BIN_2_STR=[${BIN_2_STR}]")
    message(STATUS "STR2_FLOAT=[${STR2_FLOAT}]")
    message(STATUS "STR2_MONTH=[${STR2_MONTH}]")
    message(STATUS "STRING_PARSER=[${STRING_PARSER}]")
    #message( FATAL_ERROR "STR2_DOUBLE=[${STR2_DOUBLE}]")

    add_compile_definitions(HAS_STRING)
    target_compile_definitions(app PUBLIC HAS_STRING)
    target_compile_definitions(app PUBLIC HAS_NUM_DIAG)
    
    include_directories(${STRING_DIR})
    target_include_directories(app PUBLIC ${STRING_DIR})

    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/lib/picolibc/newlib/libc/include)
    target_sources(app PRIVATE ${STRING_DIR}/str_utils.c)

    target_compile_definitions(app PUBLIC HAS_STR2_DOUBLE)
    if (Y STREQUAL STR2_DOUBLE)
        message( STATUS "Add STR2_DOUBLE")
    endif()

    if (BIN_2_STR STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BIN_2_STR)
    endif()

    if (Y STREQUAL STR2_FLOAT)
        message( STATUS "Add STR2_FLOAT")
    endif()
    target_compile_definitions(app PUBLIC HAS_STR2_FLOAT)

    if(STR2_MONTH STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_STR2_MONTH)
    endif()

    if(STRING_PARSER STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PARSE_8BIT_TYPES)
        target_compile_definitions(app PUBLIC HAS_PARSE_16BIT_TYPES)
        target_compile_definitions(app PUBLIC HAS_PARSE_32BIT_TYPES)
        target_compile_definitions(app PUBLIC HAS_PARSE_64BIT_TYPES)
        target_compile_definitions(app PUBLIC HAS_STRING_PARSER)
        target_sources(app PRIVATE ${STRING_DIR}/convert.c)
        target_sources(app PRIVATE ${STRING_DIR}/num_to_str.c)
    endif()

    if(X86_64 STREQUAL Y)
        target_sources(app PRIVATE ${STRING_DIR}/str_utils_ex.c)
    endif()

endif()
