message(STATUS "TEST_SET_SW_MK_INC=${TEST_SET_SW_MK_INC}")
if( NOT (TEST_SET_SW_MK_INC STREQUAL Y))
    set(TEST_SET_SW_MK_INC Y)
    message(STATUS "Link SW Tests")
    set(TEST_SET_SW_DIR ${UNIT_TESTS_DIR}/test_set_sw)
    message(STATUS "TEST_SET_SW_DIR=${TEST_SET_SW_DIR}")
    target_include_directories(app PUBLIC ${TEST_SET_SW_DIR})
    target_sources(app PRIVATE ${TEST_SET_SW_DIR}/test_sw_list.c)

    if(TEST_MATH STREQUAL Y)
        include(${TEST_SET_SW_DIR}/test_math/test_math.cmake)
    endif()

endif()
