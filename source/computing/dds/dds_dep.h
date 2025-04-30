#ifndef DDS_DEP_H
#define DDS_DEP_H


#ifndef HAS_DDS
#error  "+HAS_DDS"
#endif /*HAS_DDS*/

#ifndef HAS_AUDIO
#error "+HAS_AUDIO"
#endif

#ifndef HAS_ALLOCATOR
#warning "+HAS_ALLOCATOR"
#endif /*HAS_ALLOCATOR*/

#ifndef HAS_DDS
#error "+HAS_DDS"
#endif /*HAS_DDS*/

#ifndef HAS_MATH
#error "+HAS_MATH"
#endif /*HAS_MATH*/



#endif /*DDS_DEP_H*/
