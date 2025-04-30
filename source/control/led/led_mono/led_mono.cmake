
message(STATUS "LED_MONO_MK_INC=${LED_MONO_MK_INC}")
if( NOT (LED_MONO_MK_INC STREQUAL Y))
    set(LED_MONO_MK_INC Y)

    message(STATUS "+ Led driver")

    set(LED_MONO_DIR  ${LED_GENERAL_DIR}/led_mono)

    if( NOT (LED STREQUAL Y))
         message(ERROR "Add General LED driver")
    endif()

    target_include_directories(app PUBLIC ${LED_MONO_DIR})
    target_sources(app PRIVATE ${LED_MONO_DIR}/led_mono_drv.c)

    target_compile_definitions(app PUBLIC HAS_LED_MONO)
    #set(MATH Y)

    if(LED_PROC STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_LED_MONO_PROC)
    endif()

    if(DIAG STREQUAL Y)
        if(LED_MONO_DIAG STREQUAL Y)
		    message(STATUS "+ LedMonoDiag")
            target_compile_definitions(app PUBLIC HAS_LED_MONO_DIAG)
            target_sources(app PRIVATE ${LED_MONO_DIR}/led_mono_diag.c)
        endif()    
    endif()

    if(CLI STREQUAL Y)
        if(LED_MONO_COMMANDS STREQUAL Y)
		    message(STATUS "+ LED_MONO_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_LED_MONO_COMMANDS)
            target_sources(app PRIVATE ${LED_MONO_DIR}/led_mono_commands.c)
        endif()
    endif()
endif()