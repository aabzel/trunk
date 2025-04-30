message(STATUS "CALIBRATION_DATA_MK_INC=${CALIBRATION_DATA_MK_INC}")
if( NOT (CALIBRATION_DATA_MK_INC STREQUAL Y))

    set(CALIBRATION_DATA_MK_INC Y)
    message(STATUS "+CALIBRATION_DATA")

    set(CALIBRATION_DATA_DIR ${STORAGE_DIR}/calibration_data)
    message(STATUS "CALIBRATION_DATA_DIR=${CALIBRATION_DATA_DIR}")

    #@ echo ${error CALIBRATION_DATA_DIR = ${CALIBRATION_DATA_DIR))
    #@ echo ${error CFLAGS = ${CFLAGS)) 
    target_compile_definitions(app PUBLIC HAS_CALIBRATION_DATA)

    target_include_directories(app PUBLIC ${CALIBRATION_DATA_DIR})

    target_sources(app PRIVATE ${CALIBRATION_DATA_DIR}/calibration_data.c)

    if (DIAG STREQUAL Y)
        if (CALIBRATION_DATA_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_CALIBRATION_DATA_DIAG)
            target_sources(app PRIVATE ${CALIBRATION_DATA_DIR}/calibration_data_diag.c)
        endif()
    endif()

    if (CALIBRATION_DATA_WRITE STREQUAL Y)
        #@echo ${error CALIBRATION_DATA_WRITE = ${CALIBRATION_DATA_WRITE)) 
         target_compile_definitions(app PUBLIC HAS_CALIBRATION_DATA_WRITE)
    endif()

    if (CLI STREQUAL Y)
        if (CALIBRATION_DATA_COMMANDS STREQUAL Y)
             target_compile_definitions(app PUBLIC HAS_CALIBRATION_DATA_COMMANDS)
            target_sources(app PRIVATE ${CALIBRATION_DATA_DIR}/calibration_data_commands.c)
        endif()
    endif()
endif()


