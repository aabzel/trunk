message(STATUS "TEST_SOCKET_MK_INC=${TEST_SOCKET_MK_INC}")
if( NOT (TEST_SOCKET_MK_INC STREQUAL Y))
    set(TEST_SOCKET_MK_INC Y)

    message(STATUS "Link socket Test")
    set(TEST_SOCKET_DIR ${TEST_SET_SW_DIR}/test_socket)

    target_include_directories(app PUBLIC ${TEST_SOCKET_DIR})
    target_compile_definitions(app PUBLIC HAS_TEST_SUIT_SOCKET)

    target_sources(app PRIVATE ${TEST_SOCKET_DIR}/test_socket.c)
endif()
