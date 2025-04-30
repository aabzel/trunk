message(STATUS "TEST_MATH_MK_INC=${TEST_MATH_MK_INC}")
if( NOT (TEST_MATH_MK_INC STREQUAL Y))
    set(TEST_MATH_MK_INC Y)

    message(STATUS "Link Math Test")
    set(TEST_MATH_DIR ${TEST_SET_SW_DIR}/test_math)
    #add_link_options(-lm)

    target_include_directories(app PUBLIC ${TEST_MATH_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_SUIT_MATH)
    target_sources(app PRIVATE ${TEST_MATH_DIR}/test_math.c)
endif()
