/**
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2007-2012 STMicroelectronics
  *
  ******************************************************************************
  */
#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#ifdef __MWERKS__    //Metrowerk CodeWarrior
    #include <stdint.h>

    // Standard typedefs used by header files, based on ISO C standard
    typedef volatile int8_t   vint8_t;
    typedef volatile uint8_t  vuint8_t;

    typedef volatile int16_t  vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t  vint32_t;
    typedef volatile uint32_t vuint32_t;

#else
#ifdef __ghs__    //GreenHills
    #include <stdint.h>

    // Standard typedefs used by header files, based on ISO C standard
    typedef volatile int8_t   vint8_t;
    typedef volatile uint8_t  vuint8_t;

    typedef volatile int16_t  vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t  vint32_t;
    typedef volatile uint32_t vuint32_t;

#else

    // This is needed for compilers that don't have a stdint.h file

    typedef          signed   char  int8_t;
    typedef          unsigned char  uint8_t;
    typedef volatile signed   char  vint8_t;
    typedef volatile unsigned char  vuint8_t;

    typedef          signed   short int16_t;
    typedef          unsigned short uint16_t;
    typedef volatile signed   short vint16_t;
    typedef volatile unsigned short vuint16_t;

    typedef          signed   int   int32_t;
    typedef          unsigned int   uint32_t;
    typedef volatile signed   int   vint32_t;
    typedef volatile unsigned int   vuint32_t;

#endif
#endif
#endif
