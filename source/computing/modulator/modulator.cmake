message(STATUS "MATH_MK_INC=${MATH_MK_INC}")

if( NOT (MATH_MK_INC  STREQUAL  Y))
    set(MATH_MK_INC Y)
    message(STATUS "Link Math")

    set(MATH_DIR ${COMPUTING_DIR}/math)
    target_include_directories(app PUBLIC ${MATH_DIR})

    target_compile_definitions(app PUBLIC HAS_MATH)
    #add_link_options(-lm)

    #target_compile_options(app PUBLIC -lm)
    target_sources(app PRIVATE ${MATH_DIR}/utils_math.c)
    target_sources(app PRIVATE ${MATH_DIR}/vector_math.c)
    #target_link_libraries(app PUBLIC m)

    if(DIAG  STREQUAL  Y)
        target_sources(app PRIVATE ${MATH_DIR}/vector_diag.c)
    endif()
endif()
