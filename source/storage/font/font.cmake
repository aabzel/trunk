message(STATUS "FONT_MK_INC=${FONT_MK_INC}")
if(NOT (FONT_MK_INC STREQUAL Y))
    set(FONT_MK_INC Y)
    message(STATUS "+FONT")

    set(FONT_DIR ${STORAGE_DIR}/font)
    message(STATUS "FONT_DIR=${FONT_DIR}")

    add_compile_definitions(HAS_FONT)
    target_compile_definitions(app PUBLIC HAS_FONT)

    #include_directories(${FONT_DIR})
    target_include_directories(app PUBLIC ${FONT_DIR})

    target_sources(app PRIVATE ${FONT_DIR}/fonts.c)

    if(FONT_12_X_6 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_FONT_12_X_6)
    endif()

    if(FONT_16_X_8 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_FONT_16_X_8)
    endif()

    if(FONT_24_X_12 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_FONT_24_X_12)
    endif()

    if(DIAG STREQUAL Y)
    	if(FONT_DIAG STREQUAL Y)
        	message(STATUS "+FONT_DIAG")
        	target_compile_definitions(app PUBLIC HAS_FONT_DIAG)
        	target_sources(app PRIVATE ${FONT_DIR}/font_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
    	if(FONT_COMMANDS STREQUAL Y)
        	message(STATUS "+FONT_COMMANDS")
        	target_compile_definitions(app PUBLIC HAS_FONT_COMMANDS)
        	target_sources(app PRIVATE ${FONT_DIR}/font_commands.c)
        endif()
    endif()
endif()
