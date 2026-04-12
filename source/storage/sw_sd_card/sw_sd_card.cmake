message(STATUS "SW_SD_CARD_MK_INC=${SW_SD_CARD_MK_INC}")
if( NOT (SW_SD_CARD_MK_INC  STREQUAL  Y))
    set(SW_SD_CARD_MK_INC Y)
    message(STATUS "+ SW_SD_CARD")

    set(SW_SD_CARD_DIR ${ROOT_DIR}/sw_sd_card)
    message(STATUS "SW_SD_CARD_DIR=${SW_SD_CARD_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SW_SD_CARD)
    target_compile_definitions(app PUBLIC HAS_SW_SD_CARD)
    target_compile_definitions(app PUBLIC HAS_SW_SD_CARD_PROC)

    target_include_directories(app PUBLIC ${SW_SD_CARD_DIR})
    target_sources(app PRIVATE ${SW_SD_CARD_DIR}/sw_sd_card.c)

    if(DIAG  STREQUAL  Y)
        if(SW_SD_CARD_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SW_SD_CARD_DIAG)
            target_sources(app PRIVATE ${SW_SD_CARD_DIR}/sw_sd_card_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SW_SD_CARD_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SW_SD_CARD_COMMANDS)
            target_sources(app PRIVATE ${SW_SD_CARD_DIR}/sw_sd_card_commands.c)
        endif()
    endif()
endif()
