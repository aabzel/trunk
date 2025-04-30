message(STATUS "DEBUGGER_MK_INC=${DEBUGGER_MK_INC}")
if(NOT (DEBUGGER_MK_INC STREQUAL Y))
    set(DEBUGGER_MK_INC Y)
    message(STATUS "Link DEBUGGER")

    set(DEBUGGER_DIR ${CONTROL_DIR}/debugger)
    message(STATUS "DEBUGGER_DIR=${DEBUGGER_DIR}")

    add_compile_definitions(HAS_DEBUGGER)
    target_compile_definitions(app PUBLIC HAS_DEBUGGER)
    
    include_directories(${DEBUGGER_DIR})
    target_include_directories(app PUBLIC ${DEBUGGER_DIR})
    
    if(WRITE_ADDR STREQUAL Y)
    	add_compile_definitions(HAS_WRITE_ADDR)
    	target_compile_definitions(app PUBLIC HAS_WRITE_ADDR)
    endif()
    
    target_sources(app PRIVATE ${DEBUGGER_DIR}/debugger.c)
    
    target_include_directories(app PUBLIC ${WORKSPACE_LOC}/core)
    target_sources(app PRIVATE ${WORKSPACE_LOC}/core/core_driver.c)

    if(CLI STREQUAL Y)
    	if(DEBUGGER_COMMANDS STREQUAL Y)
        	message(STATUS "Link debugger commands")
        	add_compile_definitions(HAS_DEBUGGER_COMMANDS)
        	target_compile_definitions(app PUBLIC HAS_DEBUGGER_COMMANDS)
        	target_sources(app PRIVATE ${DEBUGGER_DIR}/debugger_commands.c)
        endif()
    endif()
    
endif()