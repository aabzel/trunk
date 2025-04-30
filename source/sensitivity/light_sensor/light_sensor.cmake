
message(STATUS "LIGHT_SENSOR_MONO_MK_INC=${LIGHT_SENSOR_MONO_MK_INC}")
if( NOT (LIGHT_SENSOR_MONO_MK_INC STREQUAL Y))
    set(LIGHT_SENSOR_MONO_MK_INC Y)
    
    message(STATUS "+ Led driver")

    set(LIGHT_SENSOR_MONO_DIR  ${LIGHT_SENSOR_GENERAL_DIR}/light_sensor)

    if( NOT (LIGHT_SENSOR STREQUAL Y))
         message(ERROR "Add General LIGHT_SENSOR driver")
    endif()

    target_include_directories(app PUBLIC ${LIGHT_SENSOR_MONO_DIR})
    target_sources(app PRIVATE ${LIGHT_SENSOR_MONO_DIR}/light_sensor_drv.c)

    target_compile_definitions(app PUBLIC HAS_LIGHT_SENSOR_MONO)
    #target_compile_definitions(app PUBLIC HAS_LIGHT_SENSOR_MONO_PROC)
    #set(MATH Y)

    if(DIAG STREQUAL Y)
        if(LIGHT_SENSOR_MONO_DIAG STREQUAL Y)
		    message(STATUS "+ LedMonoDiag")
            target_compile_definitions(app PUBLIC HAS_LIGHT_SENSOR_MONO_DIAG)
            target_sources(app PRIVATE ${LIGHT_SENSOR_MONO_DIR}/light_sensor_diag.c)
        endif()    
    endif()

    if(CLI STREQUAL Y)
        if(LIGHT_SENSOR_MONO_COMMANDS STREQUAL Y)
		    message(STATUS "+ LIGHT_SENSOR_MONO_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_LIGHT_SENSOR_MONO_COMMANDS)
            target_sources(app PRIVATE ${LIGHT_SENSOR_MONO_DIR}/light_sensor_commands.c)
        endif()
    endif()
endif()