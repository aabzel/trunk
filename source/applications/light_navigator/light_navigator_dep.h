#ifndef LIGHT_NAVIGATOR_DEP_H
#define LIGHT_NAVIGATOR_DEP_H

#ifndef HAS_LIGHT_NAVIGATOR
#error "+HAS_LIGHT_NAVIGATOR"
#endif

#ifndef HAS_GNSS
#warning "+HAS_GNSS"
#endif

#ifndef HAS_CALENDAR
#warning "+HAS_CALENDAR"
#endif

#ifndef HAS_PLANETARIUM
#error "+HAS_PLANETARIUM"
#endif

#ifndef HAS_PHOTORESISTOR
#warning "+HAS_PHOTORESISTOR"
#endif

#ifndef HAS_SD_CARD
#warning "+HAS_SD_CARD"
#endif

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

#ifndef HAS_EXTERNAL_RTC
#warning "+HAS_EXTERNAL_RTC"
#endif

#ifndef HAS_SCHMITT_TRIGGER
#error "+HAS_SCHMITT_TRIGGER"
#endif


#endif /* LIGHT_NAVIGATOR_DEP_H */
