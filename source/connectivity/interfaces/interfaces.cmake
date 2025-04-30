message(STATUS "INTERFACES_CMAKE_INC=${INTERFACES_CMAKE_INC}")
if( NOT (INTERFACES_CMAKE_INC STREQUAL Y))
    set(INTERFACES_CMAKE_INC Y)
    message(STATUS "+ interfaces")
    set(INTERFACES_DIR ${CONNECTIVITY_DIR}/interfaces)
    message(STATUS "INTERFACES_DIR=${INTERFACES_DIR}")
    include_directories(${INTERFACES_DIR})

    target_compile_definitions(app PUBLIC HAS_INTERFACE)
    target_compile_definitions(app PUBLIC HAS_INTERFACES)
    target_compile_definitions(app PUBLIC HAS_INTERFACES_COMMANDS)

    target_sources(app PRIVATE ${INTERFACES_DIR}/proc_interfaces.c)

    if (CAN STREQUAL Y)
        include(${INTERFACES_DIR}/can/can.cmake)
    endif()

    if (DTMF STREQUAL Y)
        include(${INTERFACES_DIR}/dtmf/dtmf.cmake)
    endif()

    if (LORA STREQUAL Y)
        include(${INTERFACES_DIR}/lora/lora.cmake)
    endif()

    if (RADIO STREQUAL Y)
        include(${INTERFACES_DIR}/radio/radio.cmake)
    endif()

    if (RS232 STREQUAL Y)
        #@echo ${error BOOT= ${BOOT))
        include(${INTERFACES_DIR}/rs232/rs232.cmake)
    endif()
    
    if (RS485 STREQUAL Y)
        #@echo ${error BOOT= ${BOOT))
        include(${INTERFACES_DIR}/rs485/rs485.cmake)
    endif()

    if (UWB STREQUAL Y)
        message(STATUS "+ UWB driver")
        include(${INTERFACES_DIR}/uwb/uwb.cmake)
    endif()

endif()