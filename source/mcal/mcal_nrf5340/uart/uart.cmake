message(STATUS "UART_NRF5340_MK_INC=${UART_NRF5340_MK_INC}")
if( NOT (UART_NRF5340_MK_INC STREQUAL Y))
    set(UART_NRF5340_MK_INC Y)
    message(STATUS "Link UART for nrf5340")

    set(UART_NRF5340_DIR ${MCAL_NRF5340_DIR}/uart)
    message(STATUS "UART_NRF5340_DIR=${UART_NRF5340_DIR}")


    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/hal)
    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/drivers)
    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/drivers)
    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/drivers/include)

    add_compile_definitions(HAS_UART)
    target_compile_definitions(app PUBLIC HAS_UART)

    include_directories(${UART_NRF5340_DIR})
    target_include_directories(app PUBLIC ${UART_NRF5340_DIR})

    target_compile_definitions(app PUBLIC NRFX_UARTE_ENABLED)

    target_sources(app PRIVATE ${UART_NRF5340_DIR}/uart_drv.c)
    if(UART0 STREQUAL Y)
	    target_compile_definitions(app PUBLIC HAS_UART0)
        target_compile_definitions(app PUBLIC NRFX_UARTE0_ENABLED=1)
    endif()

    if(UART1 STREQUAL Y)
        target_compile_definitions(app PUBLIC NRFX_UARTE1_ENABLED=1)
    endif()

    if(UART2 STREQUAL Y)
	    target_compile_definitions(app PUBLIC HAS_UART2)
        target_compile_definitions(app PUBLIC NRFX_UARTE2_ENABLED=1)
    endif()

    if(UART3 STREQUAL Y)
        target_compile_definitions(app PUBLIC NRFX_UARTE3_ENABLED=1)
    endif()

    if(UART_INTERRUPT STREQUAL Y)
	    target_compile_definitions(app PUBLIC HAS_UART_ISR)
        target_compile_definitions(app PUBLIC HAS_UART_INTERRUPT)
        target_sources(app PRIVATE ${UART_NRF5340_DIR}/uart_isr.c)
    endif()


endif()


