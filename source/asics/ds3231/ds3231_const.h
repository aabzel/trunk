
#ifndef DS3231_CONST_H
#define DS3231_CONST_H

#include "ds3231_dep.h"
#include "time_mcal.h"

#define DS3231_ADDRESS        0x68        /* device address */
#define DS3231_REG_CNT        19        /**/

#define DS3231_POLL_PERIOD_US SEC_2_USEC(5)

typedef enum {
     DS3231_REG_SECOND          =     0x00  ,      /**< second register */
     DS3231_REG_MINUTE          =     0x01  ,      /**< minute register */
     DS3231_REG_HOUR            =     0x02  ,      /**< hour register */
     DS3231_REG_WEEK            =     0x03  ,      /**< week register */
     DS3231_REG_DATE            =     0x04  ,      /**< date register */
     DS3231_REG_MONTH           =     0x05  ,      /**< month register */
     DS3231_REG_YEAR            =     0x06  ,      /**< year register */
     DS3231_REG_ALARM1_SECOND   =     0x07  ,      /**< alarm1 second register */
     DS3231_REG_ALARM1_MINUTE   =     0x08  ,      /**< alarm1 minute register */
     DS3231_REG_ALARM1_HOUR     =     0x09  ,      /**< alarm1 hour register */
     DS3231_REG_ALARM1_WEEK     =     0x0A  ,      /**< alarm1 week register */
     DS3231_REG_ALARM2_MINUTE   =     0x0B  ,      /**< alarm2 minute register */
     DS3231_REG_ALARM2_HOUR     =     0x0C  ,      /**< alarm2 hour register */
     DS3231_REG_ALARM2_WEEK     =     0x0D  ,      /**< alarm2 week register */
     DS3231_REG_CONTROL         =     0x0E  ,      /**< control register */
     DS3231_REG_STATUS          =     0x0F  ,      /**< status register */
     DS3231_REG_XTAL            =     0x10  ,      /**< xtal register */
     DS3231_REG_TEMPERATUREH    =     0x11  ,      /**< temperature high register */
     DS3231_REG_TEMPERATUREL    =     0x12  ,      /**< temperature low register */
}Ds3231RegAddr_t;

/*(see page 13 )SQUARE-WAVE OUTPUT FREQUENCY*/
typedef enum {
   RS_1_HZ=0,
   RS_1024_HZ=1,
   RS_4096_HZ=2,
   RS_8192_HZ=3,
   RS_UNDEF_HZ=4,
}Ds3231RateSelect_t;

typedef enum {
   HOUR_MODE_24H=0,
   HOUR_MODE_12H=1,

   HOUR_MODE_UNDEF=2,
}HourMode_t;


#endif /* DS3231_CONST_H */
