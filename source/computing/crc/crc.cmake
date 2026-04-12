# crc.cmake (с группировкой)
if(NOT CRC_MK_INC STREQUAL Y)
    set(CRC_MK_INC Y)
    
    set(CRC_DIR "${COMPUTING_DIR}/crc")
    include_directories(${CRC_DIR})
        
    string(APPEND MCAL_OPT " -DHAS_CRC")

    
    if(CRC_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CRC_DIAG")
        string(APPEND SOURCES_C " ${CRC_DIR}/crc_diag.c")
    endif()
    
    if(CRC8_AUTOSAR STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CRC8")
        string(APPEND MCAL_OPT " -DHAS_CRC8_AUTOSAR")
        string(APPEND SOURCES_C " ${CRC_DIR}/crc8_autosar.c")
    endif()
    
    if(CRC8 STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CRC8")
        string(APPEND SOURCES_C " ${CRC_DIR}/crc8_sae_j1850.c")
    endif()
    
    if(CRC16 STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CRC16")
        string(APPEND SOURCES_C " ${CRC_DIR}/crc16_ccitt.c")
    endif()
    
    if(CRC24 STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CRC24")
        string(APPEND SOURCES_C " ${CRC_DIR}/crc24_q.c")
    endif()
    
    if(CRC32 STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CRC32")
        string(APPEND SOURCES_C " ${CRC_DIR}/crc32.c")
    endif()
    
endif()

