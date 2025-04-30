
message(STATUS "CLOCK_ZEPHYR_MK_INC=${CLOCK_ZEPHYR_MK_INC}")
if (NOT (CLOCK_ZEPHYR_MK_INC STREQUAL Y))
    set(CLOCK_ZEPHYR_MK_INC Y)
    message(STATUS "set CLOCK_ZEPHYR_MK_INC=${CLOCK_ZEPHYR_MK_INC}")

    set(CLOCK_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/clock)
    message(STATUS "+ Clock Zephyr")

    message(STATUS "CLOCK_ZEPHYR_DIR=${CLOCK_ZEPHYR_DIR}")

    add_compile_definitions(HAS_CLOCK)
    target_compile_definitions(app PUBLIC HAS_CLOCK)

    target_sources(app PRIVATE ${CLOCK_ZEPHYR_DIR}/clock.c)

    if(CLI STREQUAL Y)
        if(CLOCK_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_CLOCK_COMMANDS)
            target_sources(app PRIVATE ${CLOCK_ZEPHYR_DIR}/clock_custom_commands.c)
        endif()
    endif()
    
    target_include_directories(app PUBLIC ${CLOCK_ZEPHYR_DIR})
endif()
