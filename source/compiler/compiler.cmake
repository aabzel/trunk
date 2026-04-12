
if(NOT COMPILER_MK_INC STREQUAL Y)
    set(COMPILER_MK_INC Y)

    string(APPEND MCAL_OPT " -DHAS_COMPILER")
    set(COMPILER_DIR "${WORKSPACE_LOC}/compiler")

    string(APPEND MCAL_OPT " -DHAS_GCC")
    include_directories(${COMPILER_DIR})
endif()