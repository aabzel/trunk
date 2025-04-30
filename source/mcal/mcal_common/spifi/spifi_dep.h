#ifndef SPIFI_DEP_H
#define SPIFI_DEP_H

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif /*HAS_SPIFI*/

#ifndef HAS_GPIO
#warning "+HAS_GPIO"
#endif /*HAS_GPIO*/

#endif /* SPIFI_DEP_H */
