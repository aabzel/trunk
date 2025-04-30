message(STATUS "CODE_GENARATOR_MK_INC=${CODE_GENARATOR_MK_INC}")
if( NOT (CODE_GENARATOR_MK_INC STREQUAL Y))
    set(CODE_GENARATOR_MK_INC Y)
    message(STATUS "+ Code Generator")

    set(MCAL_CODE_GENARATOR_DIR ${COMMON_DIR}/code_generator)

    target_include_directories(app PUBLIC ${MCAL_CODE_GENARATOR_DIR})
    target_compile_definitions(app PUBLIC HAS_CODE_GENARATOR)

endif()
