//**************************************************************************************************
// @Module  VECTOR
//! \file   vector_type.h
//! \brief  Interface of the VECTOR module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef VECTOR_EHAL_TYPES_H
#define VECTOR_EHAL_TYPES_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Get vector constants
#include "vector_constants.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! point in the set of real numbers
typedef struct {
    //! X
    FLOAT32 x;
    //! Y
    FLOAT32 y;
    //! Z
    FLOAT32 z;
} DOT;

//! vector in the set of real numbers
typedef struct {
    //! dX
    FLOAT32 dx;
    //! dY
    FLOAT32 dy;
    //! dZ
    FLOAT32 dz;
} VECTOR_F;

//! vector in the set of integer numbers
typedef struct {
    //! dX
    S32 dx;
    //! dY
    S32 dy;
    //! dZ
    S32 dz;
} VECTOR_S16;

//! Data type for a segment in 3D space
typedef struct {
    //! starting point of a segment
    DOT start;
    //! segment direction
    VECTOR_F vector;
} LINE_SEGMENT;

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************



#endif // #ifndef VECTOR_EHAL_TYPES_H

//****************************************** end of file *******************************************

