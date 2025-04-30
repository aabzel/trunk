
message(STATUS "GPIO_ZEPHYR_MK_INC=${GPIO_ZEPHYR_MK_INC}")
if( NOT (GPIO_ZEPHYR_MK_INC STREQUAL Y))
    set(GPIO_ZEPHYR_MK_INC Y)
    message(STATUS "set GPIO_ZEPHYR_MK_INC=${GPIO_ZEPHYR_MK_INC}")
    set(GPIO_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/gpio)
    message(STATUS "+ GPIO Zephyr")
    message(STATUS "GPIO_ZEPHYR_DIR=${GPIO_ZEPHYR_DIR}")

    add_compile_definitions(HAS_GPIO)
    target_compile_definitions(app PUBLIC HAS_GPIO)
    target_compile_definitions(app PUBLIC HAS_GPIO_ZEPHYR)

    if(PINS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PINS)
    endif()

    target_sources(app PRIVATE ${GPIO_ZEPHYR_DIR}/gpio_drv.c)

    target_include_directories(app PUBLIC ${GPIO_ZEPHYR_DIR})
endif()
