
if( NOT (CRC_MK_INC STREQUAL Y))
    set(CRC_MK_INC Y)
    message(STATUS "+ CRC")

    set(CRC_DIR ${COMPUTING_DIR}/crc)

    target_compile_definitions(app PUBLIC HAS_CRC)
    target_include_directories(app PUBLIC ${CRC_DIR})

    if (CRC8 STREQUAL Y)
        message(STATUS "+ CRC8")
        target_compile_definitions(app PUBLIC HAS_CRC8)
        target_sources(app PRIVATE ${CRC_DIR}/crc8_sae_j1850.c)
        target_sources(app PRIVATE ${CRC_DIR}/crc8_autosar.c)
    endif()

    if (CRC16 STREQUAL Y)
        message(STATUS "+ CRC16")
        target_compile_definitions(app PUBLIC HAS_CRC16)
        target_sources(app PRIVATE ${CRC_DIR}/crc16_ccitt.c)
    endif()

    if (CRC24 STREQUAL Y)
        message(STATUS "+ CRC24")
        target_compile_definitions(app PUBLIC HAS_CRC24)
        target_sources(app PRIVATE ${CRC_DIR}/crc24_q.c)
    endif()

    if (CRC32 STREQUAL Y)
        message(STATUS "+ CRC32")
        #@echo ${error CRC32=${CRC32))
        target_compile_definitions(app PUBLIC HAS_CRC32)
        target_sources(app PRIVATE ${CRC_DIR}/crc32.c)
    endif()
endif()

