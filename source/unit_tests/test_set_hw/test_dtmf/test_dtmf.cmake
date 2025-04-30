message(STATUS "TEST_DTMF_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_DTMF_MK_INC STREQUAL Y))
    set(TEST_DTMF_MK_INC Y)
    message(STATUS "Link Test DTMF")

    set(TEST_DTMF_DIR ${TEST_SET_HW_DIR}/test_dtmf)

    target_include_directories(app PUBLIC ${TEST_DTMF_DIR})

    target_compile_definitions(app PUBLIC HAS_TEST_DTMF)

    target_sources(app PRIVATE ${TEST_DTMF_DIR}/test_dtmf.c)
endif()