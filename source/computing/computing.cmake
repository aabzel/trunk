
if(NOT (COMPUTING_MK_INC STREQUAL Y))
    set(COMPUTING_MK_INC Y )

    string(APPEND MCAL_OPT " -DHAS_COMPUTING")
    set(COMPUTING_DIR "${WORKSPACE_LOC}/computing")
    include_directories(${COMPUTING_DIR})

    if(INTERVAL STREQUAL Y)
        include(${COMPUTING_DIR}/interval/interval.cmake)
    endif()

    if(RATIONAL_NUM STREQUAL Y)
        include(${COMPUTING_DIR}/rational_num/rational_num.cmake)
    endif()

    if(ANALOG_FILTER STREQUAL Y)
        include(${COMPUTING_DIR}/analog_filter/analog_filter.cmake)
    endif()

    if(STABLE_SORT STREQUAL Y)
        include(${COMPUTING_DIR}/stable_sort/stable_sort.cmake)
    endif()

    if(CALCULATOR STREQUAL Y)
        include(${COMPUTING_DIR}/calculator/calculator.cmake)
    endif()

    if(CLOCK_DIVIDER STREQUAL Y)
        include(${COMPUTING_DIR}/clock_divider/clock_divider.cmake)
    endif()

    if(PLL_CALC STREQUAL Y)
        include(${COMPUTING_DIR}/pll_calc/pll_calc.cmake)
    endif()

    if(PLL_SIM STREQUAL Y)
        include(${COMPUTING_DIR}/pll_sim/pll_sim.cmake)
    endif()

    if(CRC STREQUAL Y)
        include(${COMPUTING_DIR}/crc/crc.cmake)
    endif()

    if(COMPLEX STREQUAL Y)
        include(${COMPUTING_DIR}/complex/complex.cmake)
    endif()

    if(CALENDAR STREQUAL Y)
        include(${COMPUTING_DIR}/calendar/calendar.cmake)
    endif()

    if(CONVERTOR STREQUAL Y)
        include(${COMPUTING_DIR}/convertor/convertor.cmake)
    endif()

    if(DELTA_SIGMA STREQUAL Y)
        include(${COMPUTING_DIR}/delta_sigma/delta_sigma.cmake)
    endif()

    if(DSP STREQUAL Y)
        include(${COMPUTING_DIR}/dsp/dsp.cmake)
    endif()

    if(GNSS STREQUAL Y)
        include(${COMPUTING_DIR}/gnss/gnss.cmake)
    endif()

    if(IEC16022 STREQUAL Y)
        include(${COMPUTING_DIR}/iec16022/iec16022.cmake)
    endif()

    if(LIMITER STREQUAL Y)
        include(${COMPUTING_DIR}/limiter/limiter.cmake)
    endif()

    if(MATH STREQUAL Y)
        include(${COMPUTING_DIR}/math/math.cmake)
    endif()

    if(MODULATOR STREQUAL Y)
        include(${COMPUTING_DIR}/modulator/modulator.cmake)
    endif()

    if(PLANETARIUM STREQUAL Y)
        include(${COMPUTING_DIR}/planetarium/planetarium.cmake)
    endif()

    if(RLE STREQUAL Y)
        include(${COMPUTING_DIR}/rle/rle.cmake)
    endif()

    if(SHA256 STREQUAL Y)
        include(${COMPUTING_DIR}/sha256/sha256.cmake)
    endif()

    if(SOLVER STREQUAL Y)
        include(${COMPUTING_DIR}/solver/solver.cmake)
    endif()

    if(DDS STREQUAL Y)
        include(${COMPUTING_DIR}/dds/dds.cmake)
    endif()

    if(STATISTICS STREQUAL Y)
        include(${COMPUTING_DIR}/statistics/statistics.cmake)
    endif()

    if(TIMER_CALC STREQUAL Y)
        include(${COMPUTING_DIR}/timer_calc/timer_calc.cmake)
    endif()

    if(VOLTAGE_DIVIDER STREQUAL Y)
        include(${COMPUTING_DIR}/voltage_divider/voltage_divider.cmake)
    endif()

    string(APPEND SOURCES_C " ${COMPUTING_DIR}/computing.c")

    if(CLI STREQUAL Y)
        if(COMPUTING_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_COMPUTING_COMMANDS")
            string(APPEND SOURCES_C " ${COMPUTING_DIR}/computing_commands.c")
        endif()
    endif()

    if(DIAG STREQUAL Y)
        if(COMPUTING_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_COMPUTING_DIAG")
            string(APPEND SOURCES_C " ${COMPUTING_DIR}/computing_diag.c")
        endif()
    endif()

endif()