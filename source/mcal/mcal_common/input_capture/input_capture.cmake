
message(STATUS "INPUT_CAPTURE_MCAL_MK_INC=${INPUT_CAPTURE_MCAL_MK_INC}")

if( NOT (INPUT_CAPTURE_MCAL_MK_INC STREQUAL Y))
    set(INPUT_CAPTURE_MCAL_MK_INC Y)

    message(STATUS "+INPUT_CAPTURE Common Drv")

    set(INPUT_CAPTURE_MCAL_DIR ${MCAL_COMMON_DIR}/input_capture)
    #@echo ${error INPUT_CAPTURE_MCAL_DIR=${INPUT_CAPTURE_MCAL_DIR))

    target_include_directories(app PUBLIC ${INPUT_CAPTURE_MCAL_DIR})

    target_compile_definitions(app PUBLIC HAS_INPUT_CAPTURE)

    target_sources(app PRIVATE ${INPUT_CAPTURE_MCAL_DIR}/input_capture_general_drv.c)

    if (DIAG STREQUAL Y)
        if (INPUT_CAPTURE_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_INPUT_CAPTURE_DIAG)
            target_sources(app PRIVATE ${INPUT_CAPTURE_MCAL_DIR}/input_capture_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        #@echo ${error CLI=${CLI))
        if (INPUT_CAPTURE_COMMANDS STREQUAL Y)
            #@echo ${error INPUT_CAPTURE_COMMANDS=${INPUT_CAPTURE_COMMANDS))
            target_compile_definitions(app PUBLIC HAS_INPUT_CAPTURE_COMMANDS)
            target_sources(app PRIVATE ${INPUT_CAPTURE_MCAL_DIR}/input_capture_commands.c)
        endif()
    endif()
endif()


