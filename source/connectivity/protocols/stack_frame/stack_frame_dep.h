#ifndef STACK_FRAME_DEPENDENCIES_H
#define STACK_FRAME_DEPENDENCIES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_STACK_FRAME
#error  "+HAS_STACK_FRAME"
#endif /*HAS_STACK_FRAME*/

#ifndef HAS_CRC
#error "+HAS_CRC"
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifdef __cplusplus
}
#endif

#endif /* STACK_FRAME_DEPENDENCIES_H */
