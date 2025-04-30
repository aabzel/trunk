#ifndef NMEA_DEP_H
#define NMEA_DEP_H

#ifndef HAS_NMEA
#error "+HAS_NMEA"
#endif

#ifndef HAS_RTC
#error "+HAS_RTC"
#endif

#ifndef HAS_GNSS
#error "+HAS_GNSS"
#endif


#ifndef HAS_UART
#warning "+HAS_UART"
#endif

#endif /* NMEA_DEP_H */
