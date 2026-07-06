message(STATUS "ADT_CMAKE_INC=${ADT_CMAKE_INC}")
if( NOT (ADT_CMAKE_INC STREQUAL Y))
    set(ADT_CMAKE_INC Y)
    message(STATUS "+ ADT")

    set(ADT_DIR ${WORKSPACE_LOC}/adt)
    message(STATUS "ADT_DIR=${ADT_DIR}")
    include_directories(${ADT_DIR})

    target_compile_definitions(app PUBLIC HAS_ADT)

    target_sources(app PRIVATE ${ADT_DIR}/adt_proc.c)



    if (LIFO STREQUAL Y)
        include(${ADT_DIR}/lifo/lifo.cmake)
    endif()

endif()