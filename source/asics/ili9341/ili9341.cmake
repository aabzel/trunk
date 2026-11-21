message(STATUS "ILI9341_MK_INC=${ILI9341_MK_INC}")
if( NOT (ILI9341_MK_INC  STREQUAL  Y))
    set(ILI9341_MK_INC Y)
    message(STATUS "+ ILI9341")

    set(ILI9341_DIR ${ROOT_DIR}/ili9341)
    message(STATUS "ILI9341_DIR=${ILI9341_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_ILI9341)
    target_compile_definitions(app PUBLIC HAS_ILI9341)
    target_compile_definitions(app PUBLIC HAS_ILI9341_PROC)

    target_include_directories(app PUBLIC ${ILI9341_DIR})
    target_sources(app PRIVATE ${ILI9341_DIR}/ili9341.c)

    if(DIAG  STREQUAL  Y)
        if(ILI9341_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_ILI9341_DIAG)
            target_sources(app PRIVATE ${ILI9341_DIR}/ili9341_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(ILI9341_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_ILI9341_COMMANDS)
            target_sources(app PRIVATE ${ILI9341_DIR}/ili9341_commands.c)
        endif()
    endif()
endif()
