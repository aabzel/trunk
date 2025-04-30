
message(STATUS "TEST_AT24CXX_MK_INC=${TEST_AT24CXX_MK_INC}")

if( NOT (TEST_AT24CXX_MK_INC STREQUAL Y))
    set(TEST_AT24CXX_MK_INC Y)
    message(STATUS "+ AT24CXX Test")

    set(TEST_AT24CXX_DIR ${TEST_SET_HW_DIR}/test_at24cxx)

    target_include_directories(app PUBLIC ${TEST_AT24CXX_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_AT24CXX)

    target_sources(app PRIVATE ${TEST_AT24CXX_DIR}/test_at24cxx.c)
endif()