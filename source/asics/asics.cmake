message(STATUS "ASICS_CMAKE_INC=${ASICS_CMAKE_INC}")
if( NOT (ASICS_CMAKE_INC STREQUAL Y))
    set(ASICS_CMAKE_INC Y)
    message(STATUS "+ ASICS")

    set(ASICS_DIR ${WORKSPACE_LOC}/asics)
    message(STATUS "ASICS_DIR=${ASICS_DIR}")
    include_directories(${ASICS_DIR})

    target_compile_definitions(app PUBLIC HAS_ASICS)
    target_compile_definitions(app PUBLIC HAS_ASICS_COMMANDS)

    target_sources(app PRIVATE ${ASICS_DIR}/asics_drv.c)

    if (AT24CXX STREQUAL Y)
        include(${ASICS_DIR}/at24cxx/at24cxx.cmake)
    endif()

    if (BC127 STREQUAL Y)
        include(${ASICS_DIR}/bc127/bc127.cmake)
    endif()

    if (BT1026 STREQUAL Y)
        message(STATUS "+ BT1026 driver")
        include(${ASICS_DIR}/bt1026/bt1026.cmake)
    endif()

    if (BQ24079 STREQUAL Y)
        include(${ASICS_DIR}/bq24079/bq24079.cmake)
    endif()

    if (DECADRIVER STREQUAL Y)
        message(STATUS "+ DECADRIVER driver")
        include(${ASICS_DIR}/decadriver/decadriver.cmake)
    endif()

    if (DW1000 STREQUAL Y)
        message(STATUS "+ DW1000 driver")
        include(${ASICS_DIR}/dw1000/dw1000.cmake)
    endif()

    if (DWM1000 STREQUAL Y)
        message(STATUS "+ DWM1000 driver")
        include(${ASICS_DIR}/dwm1000/dwm1000.cmake)
    endif()

    if (FDA801 STREQUAL Y)
        include(${ASICS_DIR}/fda801/fda801.cmake)
    endif()

    if (MAX98357 STREQUAL Y)
        include(${ASICS_DIR}/max98357/max98357.cmake)
    endif()

    if (MAX9860 STREQUAL Y)
        include(${ASICS_DIR}/max9860/max9860.cmake)
    endif()

    if (MIC2026 STREQUAL Y)
        include(${ASICS_DIR}/mic2026/mic2026.cmake)
    endif()

    if (RS2058 STREQUAL Y)
        message(STATUS "+ RS2058 driver")
        include(${ASICS_DIR}/rs2058/rs2058.cmake)
    endif()

    if (SI4703 STREQUAL Y)
        message(STATUS "+ SI4703 driver")
        include(${ASICS_DIR}/si4703/si4703.cmake)
    endif()

    if (SI4737 STREQUAL Y)
        message(STATUS "+ SI4737 driver")
        include(${ASICS_DIR}/si4737/si4737.cmake)
    endif()

    if (SX1262 STREQUAL Y)
        message(STATUS "+ SX1262 driver")
        include(${ASICS_DIR}/sx1262/sx1262.cmake)
    endif()

    if (SSD1306 STREQUAL Y)
        message(STATUS "+ SSD1306 driver")
        include(${ASICS_DIR}/ssd1306/ssd1306.cmake)
    endif()

    if (TPA2013D1 STREQUAL Y)
        message(STATUS "+ TPA2013D1 driver")
        include(${ASICS_DIR}/tpa2013d1/tpa2013d1.cmake)
    endif()

    if (WM8731 STREQUAL Y)
        message(STATUS "+ WM8731 driver")
        include(${ASICS_DIR}/wm8731/wm8731.cmake)
    endif()

    if (ZED_F9P STREQUAL Y)
        message(STATUS "+ ZED_F9P driver")
        include(${ASICS_DIR}/zed_f9p/zed_f9p.cmake)
    endif()
endif()