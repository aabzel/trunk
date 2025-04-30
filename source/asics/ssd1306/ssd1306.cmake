message(STATUS "SSD1306_MK_INC=${SSD1306_MK_INC}")
if( NOT (SSD1306_MK_INC  STREQUAL  Y))
    set(SSD1306_MK_INC Y)
    message(STATUS "+ SSD1306")

    set(SSD1306_DIR ${ASICS_DIR}/ssd1306)
    message(STATUS "SSD1306_DIR=${SSD1306_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SSD1306)
    target_compile_definitions(app PUBLIC HAS_SSD1306)
    target_compile_definitions(app PUBLIC HAS_SSD1306_PROC)

    target_include_directories(app PUBLIC ${SSD1306_DIR})
    target_sources(app PRIVATE ${SSD1306_DIR}/ssd1306_drv.c)

    if(DIAG  STREQUAL  Y)
        if(SSD1306_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SSD1306_DIAG)
            target_sources(app PRIVATE ${SSD1306_DIR}/ssd1306_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SSD1306_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SSD1306_COMMANDS)
            target_sources(app PRIVATE ${SSD1306_DIR}/ssd1306_commands.c)
        endif()
    endif()
endif()
