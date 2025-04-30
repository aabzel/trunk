
message(STATUS "TEST_WM8731_MK_INC=${TEST_WM8731_MK_INC}")

if( NOT (TEST_WM8731_MK_INC STREQUAL Y))
    set(TEST_WM8731_MK_INC Y)
    message(STATUS "Add WM8731 Test")

    set(TEST_WM8731_DIR ${TEST_SET_HW_DIR}/test_wm8731)

    target_include_directories(app PUBLIC ${TEST_WM8731_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_WM8731)

    target_sources(app PRIVATE ${TEST_WM8731_DIR}/test_wm8731.c)
endif()