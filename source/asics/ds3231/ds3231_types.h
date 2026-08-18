
#ifndef DS3231_TYPES_H
#define DS3231_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "ds3231_const.h"

typedef struct {
   uint8_t reg_addr;
   char *name;
}Ds3231Reg_t;


typedef struct {
    uint16_t year;                 /**< year */
    uint8_t month;                 /**< month */
    uint8_t week;                  /**< week */
    uint8_t date;                  /**< date */
    uint8_t hour;                  /**< hour */
    uint8_t minute;                /**< minute */
    uint8_t second;                /**< second */
} Ds3231Time_t;

typedef union {
    uint8_t reg_val;
    struct {
        uint8_t a1ie :1; /* Alarm Interrupt Enable */
        uint8_t a2ie :1; /* Alarm Interrupt Enable */
        uint8_t intcn:1; /* Interrupt Control*/
        uint8_t rs   :2; /* Rate Select1*/
        uint8_t conv :1; /* Convert Temperature*/
        uint8_t bbsqw:1; /* Battery-Backed Square-Wave Enable*/
        uint8_t eosc :1; /* Enable Oscillator*/
    };
}Ds3231RegControl_t;


typedef union {
    uint8_t reg_val;
    struct {
        uint8_t seconds :4; /* Seconds*/
        uint8_t ten_seconds :3; /*10 Seconds */
        uint8_t res:1; /* */

    };
}Ds3231RegSeconds_t;

typedef union {
    uint8_t reg_val;
    struct {
        uint8_t minutes :4; /* Minutes*/
        uint8_t ten_minutes:3; /*10 Minutes */
        uint8_t res:1; /* */

    };
}Ds3231RegMinutes_t;

/*Addr 02h*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t hours_24 :4; /* Hours*/
        uint8_t ten_hour_24:2; /*10 Minutes */
        uint8_t hour_format_24:1; /*0=24 1=12*/
        uint8_t res1:1; /* */
    };
    struct {
        uint8_t hours_12 :4; /* Hours*/
        uint8_t ten_hour_12:1; /*10 Minutes */
        uint8_t am_pm:1; /*0-AM 1-PM */
        uint8_t hour_format_12:1; /*0 or 1 */
        uint8_t res2:1; /* */
    };
}Ds3231RegHours_t;


/*Addr 03h*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t week_day :3; /* week day*/
        uint8_t res:5; /* */
    };
}Ds3231RegWeekDay_t;

/*Addr 04h*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t date :4; /* Date*/
        uint8_t ten_date:2; /* 10 Date*/
        uint8_t res:2; /* */
    };
}Ds3231RegDate_t;

/*Addr 05h*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t month :4; /* Month*/
        uint8_t ten_month:1; /* 10 Month*/
        uint8_t res:2; /* */
        uint8_t century:1; /* */
    };
}Ds3231RegMonth_t;

/*Addr 06h*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t year :4; /* Year*/
        uint8_t ten_year:4; /* 10 Year*/
    };
}Ds3231RegYear_t;

/*Addr 07h*/
typedef union {
	uint8_t reg_val;
}Ds3231RegAlarm1Seconds_t ;

/*Addr 08h*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAlarm1Minutes_t ;

/*Addr 09h*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAlarm1Hours_t ;

/*Addr 0Ah*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAlarm1DayDate_t ;

/*Addr 0Bh*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAlarm2Minutes_t ;

/*Addr 0Ch*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAlarm2Hours_t ;

/*Addr 0Dh*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAlarm2DayDate_t ;


/*Addr 0Fh*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :2; /* xxxx*/
        uint8_t busy :1; /* xxxx*/
        uint8_t en32khz :1; /* xxxx*/
        uint8_t xxx2:3; /* xxxx*/
        uint8_t osc:1; /* BIT 7 OSF*/
    };
}Ds3231RegControlStatus_t ;

/*Addr 10Fh*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegAgingOffset_t ;

/*Addr 11h*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegMSBofTemp_t ;

/*Addr 12h*/
typedef union {
	uint8_t reg_val;
    struct {
        uint8_t xxx1 :4; /* xxxx*/
        uint8_t xxx2:4; /* xxxx*/
    };
}Ds3231RegLSBofTemp_t ;


typedef union {
    uint8_t buff[DS3231_REG_CNT];
    struct {
    	Ds3231RegSeconds_t Seconds;
    	Ds3231RegMinutes_t Minutes;
    	Ds3231RegHours_t Hours;
    	Ds3231RegWeekDay_t WeekDay;
    	Ds3231RegDate_t Date;
    	Ds3231RegMonth_t Month;
        Ds3231RegYear_t Year;
        Ds3231RegAlarm1Seconds_t Alarm1Seconds;
        Ds3231RegAlarm1Minutes_t Alarm1Minutes;
        Ds3231RegAlarm1Hours_t Alarm1Hours;
        Ds3231RegAlarm1DayDate_t Alarm1DayDate;
        Ds3231RegAlarm2Minutes_t Alarm2Minutes;
        Ds3231RegAlarm2Hours_t Alarm2Hours;
        Ds3231RegAlarm2DayDate_t Alarm2DayDate;
        Ds3231RegControl_t Control;
        Ds3231RegControlStatus_t ControlStatus;
        Ds3231RegAgingOffset_t AgingOffset;
        Ds3231RegMSBofTemp_t MSBofTemp;
        Ds3231RegLSBofTemp_t LSBofTemp;
    };
}RegMap_t;


typedef struct {
   uint8_t reg_addr;
   //Ds3231RegGeneral_t value;
}Ds3231RegConfig_t;


typedef struct {
    uint8_t num;
    uint8_t i2c_num;
    uint16_t temp_code;
    double temp;
    bool valid;
    bool init;
    HourMode_t hour_mode;
    RegMap_t RegMap;

    struct tm time_date;
	Ds3231RegSeconds_t Seconds;
	Ds3231RegMinutes_t Minutes;
	Ds3231RegHours_t Hours;
	Ds3231RegWeekDay_t WeekDay;
	Ds3231RegDate_t Date;
	Ds3231RegMonth_t Month;
    Ds3231RegYear_t Year;
	Ds3231RegControlStatus_t Status;
}Ds3231Handle_t;

typedef struct{
    uint8_t num;
    uint8_t i2c_num;
    bool valid;
    HourMode_t hour_mode;
    int8_t offset;
    Ds3231RateSelect_t rate_select;
}Ds3231Config_t;

#endif /* DS3231_TYPES_H */
