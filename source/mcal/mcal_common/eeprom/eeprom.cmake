
message(STATUS "EEPROM_MCAL_MK_INC=${EEPROM_MCAL_MK_INC}")

if( NOT (EEPROM_MCAL_MK_INC STREQUAL Y))
    set(EEPROM_MCAL_MK_INC Y)

    message(STATUS "+EEPROM DRV")

    set(EEPROM_MCAL_DIR ${MCAL_COMMON_DIR}/eeprom)
    #@echo ${error EEPROM_MCAL_DIR=${EEPROM_MCAL_DIR))

    target_include_directories(app PUBLIC ${EEPROM_MCAL_DIR})

    target_compile_definitions(app PUBLIC HAS_EEPROM)

    target_sources(app PRIVATE ${EEPROM_MCAL_DIR}/eeprom_general_drv.c)

    set(CRC16 Y)
    target_compile_definitions(app PUBLIC HAS_CRC16)

    if (EEPROM_EX STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_EEPROM_EX)
    endif()

    if (EEPROM_WRITE STREQUAL Y)
        #@echo ${error EEPROM_WRITE=${EEPROM_WRITE))
        target_compile_definitions(app PUBLIC HAS_EEPROM_WRITE)
    endif()

    if (DIAG STREQUAL Y)
        if (EEPROM_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_EEPROM_DIAG)
            target_sources(app PRIVATE ${EEPROM_MCAL_DIR}/eeprom_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        #@echo ${error CLI=${CLI))
        if (EEPROM_COMMANDS STREQUAL Y)
            #@echo ${error EEPROM_COMMANDS=${EEPROM_COMMANDS))
            target_compile_definitions(app PUBLIC HAS_EEPROM_COMMANDS)
            target_sources(app PRIVATE ${EEPROM_MCAL_DIR}/eeprom_commands.c)
        endif()
    endif()
endif()


