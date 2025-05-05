#ifndef AUTO_BRIGHTNESS_DEP_H
#define AUTO_BRIGHTNESS_DEP_H

#ifndef HAS_AUTO_BRIGHTNESS
#warning "+HAS_AUTO_BRIGHTNESS"
#endif

#ifndef HAS_MCU
#warning "+HAS_MCU"
#endif

#ifndef HAS_PWM
#warning "+HAS_PWM"
#endif

#ifndef HAS_DISTANCE
#error "+HAS_DISTANCE"
#endif

#endif /* AUTO_BRIGHTNESS_DEP_H */
