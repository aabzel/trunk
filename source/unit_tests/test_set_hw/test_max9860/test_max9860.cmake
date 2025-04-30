
message(STATUS "TEST_MAX9860_MK_INC=${TEST_MAX9860_MK_INC}")

if( NOT (TEST_MAX9860_MK_INC STREQUAL Y))
    set(TEST_MAX9860_MK_INC Y)
    message(STATUS "Add MAX9860 Test")

    set(TEST_MAX9860_DIR ${TEST_SET_HW_DIR}/test_max9860)

    target_include_directories(app PUBLIC ${TEST_MAX9860_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_MAX9860)

    target_sources(app PRIVATE ${TEST_MAX9860_DIR}/test_max9860.c)
endif()