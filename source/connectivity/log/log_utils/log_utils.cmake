message(STATUS "LOG_UTILS_MK_INC=${LOG_UTILS_MK_INC}")
if( NOT (LOG_UTILS_MK_INC STREQUAL Y))
    set(LOG_UTILS_MK_INC Y)
    message(STATUS "+ Log utils")

    set(LOG_UTILS_DIR ${LOG_DIR}/log_utils)
    message(STATUS "LOG_UTILS_DIR=${LOG_UTILS_DIR}")

    add_compile_definitions(HAS_LOG_UTILS)
    include_directories(${LOG_UTILS_DIR})

    target_compile_definitions(app PUBLIC HAS_LOG_UTILS)

    if(STR2_DOUBLE STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_STR2_DOUBLE)
    endif()

    target_include_directories(app PUBLIC ${LOG_UTILS_DIR})
    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/zephyr/include/zephyr/sys)
    

    target_sources(app PRIVATE ${LOG_UTILS_DIR}/log_utils.c)
    target_sources(app PRIVATE ${LOG_UTILS_DIR}/oprintf.c)
    target_sources(app PRIVATE ${LOG_UTILS_DIR}/string_writer.c)
    target_sources(app PRIVATE ${LOG_UTILS_DIR}/ostream.c)
    target_sources(app PRIVATE ${LOG_UTILS_DIR}/writer_config.c)
    target_sources(app PRIVATE ${LOG_UTILS_DIR}/writer_generic.c)

    if (CUSTOM_PRINTF STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_CUSTOM_PRINTF)
        target_sources(app PRIVATE ${LOG_UTILS_DIR}/print_format.c)
    endif()

    if (UART STREQUAL Y)
        target_sources(app PRIVATE ${LOG_UTILS_DIR}/writer_uart.c)
    endif()

    if (X86 STREQUAL Y)
        target_sources(app PRIVATE ${LOG_UTILS_DIR}/writer_stdout.c)
    endif()
endif()






 