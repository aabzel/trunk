message(STATUS "SCHMITT_TRIGGER_MK_INC=${SCHMITT_TRIGGER_MK_INC}")
if( NOT (SCHMITT_TRIGGER_MK_INC  STREQUAL Y))
    set(SCHMITT_TRIGGER_MK_INC Y)

    message(STATUS "+ SchmittTrigger driver")

    set(SCHMITT_TRIGGER_DIR  ${COMPUTING_DIR}/schmitt_trigger)

    add_compile_definitions(HAS_SCHMITT_TRIGGER)
    target_compile_definitions(app PUBLIC HAS_SCHMITT_TRIGGER)

    target_include_directories(app PUBLIC ${SCHMITT_TRIGGER_DIR})
    target_sources(app PRIVATE ${SCHMITT_TRIGGER_DIR}/schmitt_trigger.c)

    if(DIAG  STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SCHMITT_TRIGGER_DIAG)
        target_sources(app PRIVATE ${SCHMITT_TRIGGER_DIR}/schmitt_trigger_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(SCHMITT_TRIGGER_COMMANDS  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SCHMITT_TRIGGER_COMMANDS)
            target_sources(app PRIVATE ${SCHMITT_TRIGGER_DIR}/schmitt_trigger_commands.c)
        endif()
    endif()
endif()