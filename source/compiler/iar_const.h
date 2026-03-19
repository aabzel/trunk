#ifndef IAR_CONST_H
#define IAR_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 If you want to use these features, add
 #include "compiler_const.h"
*/

// defaul function implementation
#define _WEAK_FUN_ __weak
#define _PACKED_ __packed


#define _INTERRUPT_

/*
This built-in function represents all anonymous arguments of
an inline function. It can be used only in inline functions
that are always inlined, never compiled as a separate function,
such as those using */
#define _INLINE_FUN_ inline

// Compiler keyword for placing an object at an absolute address (global variable address modifier)
// Usage example: unsigned char My_Array[3] AT_ADDR(0x0810C000) = {0x12, 0x15, 0x78};
//#define PLACE_AT_ADDR(address)

//   void __nop( void );
// Generates a NOP instruction
#define _NOP_()

//   void INTERRUPT_ENABLE(void);
//  Interrupt enable
#define INTERRUPT_ON()

//   void INTERRUPT_DISABLE(void);
//  Interrupt disable
#define INTERRUPT_OFF()

//#define __NO_RETURN _Pragma("object_attribute=__noreturn")

#ifdef __cplusplus
}
#endif

#endif /* IAR_CONST_H */
