
message(STATUS "TEST_MX25R6435F_MK_INC=${TEST_MX25R6435F_MK_INC}")

if( NOT (TEST_MX25R6435F_MK_INC STREQUAL Y))
    set(TEST_MX25R6435F_MK_INC Y)
    message(STATUS "Add MX25R6435F Test")

    set(TEST_MX25R6435F_DIR ${TEST_SET_HW_DIR}/test_mx25r6435f)

    target_include_directories(app PUBLIC ${TEST_MX25R6435F_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_MX25R6435F)

    target_sources(app PRIVATE ${TEST_MX25R6435F_DIR}/test_mx25r6435f.c)
endif()