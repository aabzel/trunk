message(STATUS "TEST_PLANETARIUM_MK_INC=${TEST_PLANETARIUM_MK_INC}")
if( NOT (TEST_PLANETARIUM_MK_INC STREQUAL Y))
    set(TEST_PLANETARIUM_MK_INC Y)

    message(STATUS "Link Math Test")
    set(TEST_PLANETARIUM_DIR ${TEST_SET_SW_DIR}/test_math)
    #add_link_options(-lm)

    target_include_directories(app PUBLIC ${TEST_PLANETARIUM_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_SUIT_PLANETARIUM)
    target_sources(app PRIVATE ${TEST_PLANETARIUM_DIR}/test_math.c)
endif()
