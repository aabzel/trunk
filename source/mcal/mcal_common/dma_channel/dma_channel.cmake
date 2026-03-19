message(STATUS "DMA_CHANNEL_MK_INC=${DMA_CHANNEL_MK_INC}")
if( NOT (DMA_CHANNEL_MK_INC  STREQUAL  Y))
    set(DMA_CHANNEL_MK_INC Y)
    message(STATUS "+ DMA_CHANNEL")

    set(DMA_CHANNEL_DIR ${ROOT_DIR}/dma_channel)
    message(STATUS "DMA_CHANNEL_DIR=${DMA_CHANNEL_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_DMA_CHANNEL)
    target_compile_definitions(app PUBLIC HAS_DMA_CHANNEL)
    target_compile_definitions(app PUBLIC HAS_DMA_CHANNEL_PROC)

    target_include_directories(app PUBLIC ${DMA_CHANNEL_DIR})
    target_sources(app PRIVATE ${DMA_CHANNEL_DIR}/dma_channel.c)

    if(DIAG  STREQUAL  Y)
        if(DMA_CHANNEL_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DMA_CHANNEL_DIAG)
            target_sources(app PRIVATE ${DMA_CHANNEL_DIR}/dma_channel_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(DMA_CHANNEL_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DMA_CHANNEL_COMMANDS)
            target_sources(app PRIVATE ${DMA_CHANNEL_DIR}/dma_channel_commands.c)
        endif()
    endif()
endif()
