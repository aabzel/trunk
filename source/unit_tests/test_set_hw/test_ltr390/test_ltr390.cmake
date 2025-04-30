
message(STATUS "TEST_LTR390_MK_INC=${TEST_LTR390_MK_INC}")

if( NOT (TEST_LTR390_MK_INC STREQUAL Y))
    set(TEST_LTR390_MK_INC Y)
    message(STATUS "+ LTR390 Test")

    set(TEST_LTR390_DIR ${TEST_SET_HW_DIR}/test_ltr390)

    target_include_directories(app PUBLIC ${TEST_LTR390_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_LTR390)

    target_sources(app PRIVATE ${TEST_LTR390_DIR}/test_ltr390.c)
endif()