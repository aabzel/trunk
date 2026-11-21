
message(STATUS "TEST_ILI9341_MK_INC=${TEST_ILI9341_MK_INC}")

if( NOT (TEST_ILI9341_MK_INC STREQUAL Y))
    set(TEST_ILI9341_MK_INC Y)
    message(STATUS "Add ILI9341 Test")

    set(TEST_ILI9341_DIR ${TEST_SET_HW_DIR}/test_ili9341)

    target_include_directories(app PUBLIC ${TEST_ILI9341_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_ILI9341)

    target_sources(app PRIVATE ${TEST_ILI9341_DIR}/test_ili9341.c)
endif()