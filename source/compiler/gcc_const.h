#ifndef GCC_CONST_H
#define GCC_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 If you want to use these features, add
 #include "compiler_const.h"
*/

// defaul function implementation
#define _WEAK_FUN_  __attribute__((weak))
#define _PACKED_  __attribute__((__packed__))
//#define _PACKED_  __attribute__ ((packed))

#define _INTERRUPT_           __attribute__ ((interrupt))


#define _INLINE_FUN_          inline __attribute__((always_inline))

// Compiler keyword for placing an object at an absolute address (global variable address modifier)
// Usage example: unsigned char My_Array[3] AT_ADDR(0x0810C000) = {0x12, 0x15, 0x78};
#define PLACE_AT_ADDR(address)    __attribute__ ((section (".address_"#address)))

//   void __nop( void );
// Generates a NOP instruction
#define _NOP_()                               __asm("nop");  // TBD

//   void INTERRUPT_ENABLE(void);
//  Interrupt enable
#define INTERRUPT_ON()                  __asm__("cpsie i");

//   void INTERRUPT_DISABLE(void);
//  Interrupt disable
#define INTERRUPT_OFF()                 __asm__("cpsid i");

#ifdef __cplusplus
}
#endif

#endif /* GCC_CONST_H */
