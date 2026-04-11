if(NOT CONTROL_MBR_MK_INC STREQUAL Y)
    set(CONTROL_MBR_MK_INC Y)

    set(MBR_DIR "${CONTROL_DIR}/mbr")

    include_directories(${MBR_DIR})

    string(APPEND MCAL_OPT " -DHAS_MBR")
    string(APPEND MCAL_OPT " -DHAS_MBR_PROC")
    string(APPEND MCAL_OPT " -DHAS_MBR_INIT")

    if(GCC STREQUAL Y)
        string(APPEND LDFLAGS " -specs=nosys.specs")
    endif()

    string(APPEND SOURCES_C " ${MBR_DIR}/mbr_drv.c")
endif()