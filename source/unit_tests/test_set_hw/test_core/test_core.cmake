
message(STATUS "TEST_CORE_MK_INC=${TEST_CORE_MK_INC}")

if( NOT (TEST_CORE_MK_INC STREQUAL Y))
    set(TEST_CORE_MK_INC Y)
    message(STATUS "Add CORE Test")

    set(TEST_CORE_DIR ${TEST_SET_HW_DIR}/test_core)

    target_include_directories(app PUBLIC ${TEST_CORE_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_CORE)
    target_compile_definitions(app PUBLIC HAS_TEST_SUIT_CORE)

    target_sources(app PRIVATE ${TEST_CORE_DIR}/test_core.c)
endif()