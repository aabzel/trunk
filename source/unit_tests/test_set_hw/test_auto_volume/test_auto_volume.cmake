
message(STATUS "TEST_AUTO_VOLUME_MK_INC=${TEST_AUTO_VOLUME_MK_INC}")

if( NOT (TEST_AUTO_VOLUME_MK_INC STREQUAL Y))
    set(TEST_AUTO_VOLUME_MK_INC Y)
    message(STATUS "Add AUTO_VOLUME Test")

    set(TEST_AUTO_VOLUME_DIR ${TEST_SET_HW_DIR}/test_auto_volume)

    target_include_directories(app PUBLIC ${TEST_AUTO_VOLUME_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_AUTO_VOLUME)

    target_sources(app PRIVATE ${TEST_AUTO_VOLUME_DIR}/test_auto_volume.c)
endif()