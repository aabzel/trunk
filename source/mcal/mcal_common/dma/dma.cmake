message(STATUS "DMA_MK_INC=${DMA_MK_INC}")
if( NOT (DMA_MK_INC  STREQUAL  Y))
    set(DMA_MK_INC Y)
    message(STATUS "+ DMA")

    set(DMA_DIR ${ROOT_DIR}/dma)
    message(STATUS "DMA_DIR=${DMA_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_DMA)
    target_compile_definitions(app PUBLIC HAS_DMA)
    target_compile_definitions(app PUBLIC HAS_DMA_PROC)

    target_include_directories(app PUBLIC ${DMA_DIR})
    target_sources(app PRIVATE ${DMA_DIR}/dma.c)

    if(DIAG  STREQUAL  Y)
        if(DMA_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DMA_DIAG)
            target_sources(app PRIVATE ${DMA_DIR}/dma_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(DMA_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DMA_COMMANDS)
            target_sources(app PRIVATE ${DMA_DIR}/dma_commands.c)
        endif()
    endif()
endif()
