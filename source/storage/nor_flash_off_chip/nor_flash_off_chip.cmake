message(STATUS "NOR_FLASH_OFF_CHIP_MK_INC=${NOR_FLASH_OFF_CHIP_MK_INC}")
if( NOT (NOR_FLASH_OFF_CHIP_MK_INC STREQUAL Y))
    set(NOR_FLASH_OFF_CHIP_MK_INC Y)
    message(STATUS "+ Mx25r6435f")

    set(NOR_FLASH_OFF_CHIP_DIR ${STORAGE_DIR}/nor_flash_off_chip)
    message(STATUS "NOR_FLASH_OFF_CHIP_DIR=${NOR_FLASH_OFF_CHIP_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_NOR_FLASH_OFF_CHIP)
    target_compile_definitions(app PUBLIC HAS_NOR_FLASH_OFF_CHIP)

    target_include_directories(app PUBLIC ${NOR_FLASH_OFF_CHIP_DIR})
    target_sources(app PRIVATE ${NOR_FLASH_OFF_CHIP_DIR}/nor_flash_off_chip_api.c)

endif()
