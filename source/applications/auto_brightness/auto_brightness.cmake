message(STATUS "AUTO_BRIGHTNESS_MK_INC=${AUTO_BRIGHTNESS_MK_INC}")
if( NOT (AUTO_BRIGHTNESS_MK_INC STREQUAL Y))
    set(AUTO_BRIGHTNESS_MK_INC Y)
    message(STATUS "+ AUTO_BRIGHTNESS")

    set(AUTO_BRIGHTNESS_DIR ${APPLICATIONS_DIR}/auto_brightness)

    target_include_directories(app PUBLIC ${AUTO_BRIGHTNESS_DIR})

    target_compile_definitions(app PUBLIC HAS_AUTO_BRIGHTNESS)
    target_compile_definitions(app PUBLIC HAS_AUTO_BRIGHTNESS_PROC)

    target_sources(app PRIVATE ${AUTO_BRIGHTNESS_DIR}/auto_brightness.c)

    if(DIAG STREQUAL Y)
        if(AUTO_BRIGHTNESS_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_AUTO_BRIGHTNESS_DIAG)
            target_sources(app PRIVATE ${AUTO_BRIGHTNESS_DIR}/auto_brightness_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(AUTO_BRIGHTNESS_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_AUTO_BRIGHTNESS_COMMANDS)
            target_sources(app PRIVATE ${AUTO_BRIGHTNESS_DIR}/auto_brightness_commands.c)
        endif()
    endif()
endif()
