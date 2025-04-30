/*
 * see
 * https://ru.wikipedia.org/wiki/Time.h
 * https://istarik.ru/blog/stm32/116.html
 * */

#include "rtc_mcal.h"

//#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "debugger.h"
#include "stm32f4xx_hal.h"
#include "hal_diag.h"
#include "log.h"


static const RtcInfo_t RtcInfo[] = {
    {
    .RTCx=RTC,
    .valid=true,
    .num=1,
    .wkup_irq_n=RTC_WKUP_IRQn,
    .alarm_irq_n=RTC_Alarm_IRQn,
    .clock_bus=CLOCK_BUS_APB1,
    },
};

COMPONENT_GET_INFO(Rtc)



static uint32_t RtcFprmatToStmFormat(RtcFormat_t format) {
    uint32_t hour_format = RTC_HOURFORMAT_24;
    switch (format) {
    case RTC_FORMAT_12H:
        hour_format = RTC_HOURFORMAT_12;
        break;
    case RTC_FORMAT_24H:
        hour_format = RTC_HOURFORMAT_24;
        break;
    default:
        break;
    }
    return hour_format;
}

bool rtc_internal_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_RTC,"Init,Internal");
    RtcHandle_t *Node = RtcGetNode(num);
    if (Node) {
        ASSERT_CRITICAL( RTC_MONTH_JANUARY     ==       0x01   );
        ASSERT_CRITICAL( RTC_MONTH_FEBRUARY    ==       0x02   );
        ASSERT_CRITICAL( RTC_MONTH_MARCH       ==       0x03   );
        ASSERT_CRITICAL( RTC_MONTH_APRIL       ==       0x04   );
        ASSERT_CRITICAL( RTC_MONTH_MAY         ==       0x05   );
        ASSERT_CRITICAL( RTC_MONTH_JUNE        ==       0x06   );
        ASSERT_CRITICAL( RTC_MONTH_JULY        ==       0x07   );
        ASSERT_CRITICAL( RTC_MONTH_AUGUST      ==       0x08   );
        ASSERT_CRITICAL( RTC_MONTH_SEPTEMBER   ==       0x09   );
        ASSERT_CRITICAL( RTC_MONTH_OCTOBER     ==       0x10   );
        ASSERT_CRITICAL( RTC_MONTH_NOVEMBER    ==       0x11   );
        ASSERT_CRITICAL( RTC_MONTH_DECEMBER    ==       0x12   );
        Node->h_rtc.Instance = RTC;
        Node->h_rtc.Init.HourFormat = RtcFprmatToStmFormat(Node->format);
        Node->h_rtc.Init.AsynchPrediv = 127;
        Node->h_rtc.Init.SynchPrediv = 255;
        Node->h_rtc.Init.OutPut = RTC_OUTPUT_DISABLE;
        Node->h_rtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
        Node->h_rtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

        HAL_StatusTypeDef ret = HAL_RTC_Init(&Node->h_rtc);
        if (HAL_OK==ret) {
            LOG_INFO(LG_RTC,"Init,Internal,Ok");
            res = true;
        } else {
            LOG_ERROR(LG_RTC,"Init,Internal,Err:%u=[%s]",ret,HalStatus2Str(ret));
            res = false;
        }
    }
    return res;
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle){
    if(rtcHandle->Instance==RTC) {
        RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
        HAL_StatusTypeDef ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
        if (HAL_OK==ret) {
            __HAL_RCC_RTC_ENABLE();
            HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 5, 5);
            HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
            HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 5, 5);
            HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
        }
    }
}


void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle) {
    if (rtcHandle->Instance == RTC) {
        //__HAL_RCC_RTC_DISABLE();
          __HAL_RCC_RTC_DISABLE();
          HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);
          HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
    }
}

bool rtc_internal_set_time(uint8_t num, const struct tm *const DateTime) {
    bool res = false;
    RtcHandle_t *Node = RtcGetNode(num);
    if(Node){
        RTC_TimeTypeDef HalTime = {0};
        HalTime.Hours = DateTime->tm_hour;
        HalTime.Minutes = DateTime->tm_min;
        HalTime.Seconds = DateTime->tm_sec;
        HalTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
        HalTime.StoreOperation = RTC_STOREOPERATION_RESET;
        HAL_StatusTypeDef ret = HAL_RTC_SetTime(&Node->h_rtc, &HalTime, RTC_FORMAT_BIN);
        if (HAL_OK==ret) {
            LOG_INFO(LG_RTC,"Set,Time,Ok");
             res = true;
        } else {
            LOG_ERROR(LG_RTC,"Set,Time,Err:%s",HalStatus2Str(ret));
            res = false;
        }
    }

    return res;
}


/*
 *  month - [0,11]
 *
 */
static uint8_t RtcMotchToStmHalMonth(int tm_mon) {
    uint8_t stm_hal_month=0;
    switch(tm_mon){
        case 0: stm_hal_month=1; break;
        case 1: stm_hal_month=2; break;
        case 2: stm_hal_month=3; break;
        case 3: stm_hal_month=4; break;
        case 4: stm_hal_month=5; break;
        case 5: stm_hal_month=6; break;
        case 6: stm_hal_month=7; break;
        case 7: stm_hal_month=8; break;
        case 8: stm_hal_month=9; break;
        case 9: stm_hal_month=10; break;
        case 10: stm_hal_month=11; break;
        case 11: stm_hal_month=12; break;
        default: LOG_ERROR(LG_RTC,"Month,Err,%u",tm_mon);     break;
    }

    return stm_hal_month;
}


static uint8_t RtcWeekDayToStmHalWeekDay(int tm_wday) {
    uint8_t stm_hal_month=0;
    switch(tm_wday){
        case 0: stm_hal_month=RTC_WEEKDAY_SUNDAY; break;
        case 1: stm_hal_month=RTC_WEEKDAY_MONDAY; break;
        case 2: stm_hal_month=RTC_WEEKDAY_TUESDAY; break;
        case 3: stm_hal_month=RTC_WEEKDAY_WEDNESDAY; break;
        case 4: stm_hal_month=RTC_WEEKDAY_THURSDAY; break;
        case 5: stm_hal_month=RTC_WEEKDAY_FRIDAY; break;
        case 6: stm_hal_month=RTC_WEEKDAY_SATURDAY; break;
        default: LOG_ERROR(LG_RTC,"WeekDay,Err");     break;
    }

    return stm_hal_month;
}


bool rtc_internal_set_date(uint8_t num, const struct tm *const DateTime) {
    bool res = false;
    RtcHandle_t *Node = RtcGetNode(num);
    if(Node){
        RTC_DateTypeDef HalDate = {0};
        HalDate.WeekDay = RtcWeekDayToStmHalWeekDay(DateTime->tm_wday) ;
        HalDate.Month =  RtcMotchToStmHalMonth(DateTime->tm_mon);
        HalDate.Date = DateTime->tm_mday;
        HalDate.Year = DateTime->tm_year-RTC_HAL_START_YEAR;
        HAL_StatusTypeDef ret = HAL_RTC_SetDate(&Node->h_rtc, &HalDate, RTC_FORMAT_BIN) ;
        if (HAL_OK==ret) {
            LOG_INFO(LG_RTC,"Set,Date,Ok");
             res = true;
        } else {
            LOG_ERROR(LG_RTC,"Set,Date,Err:%s",HalStatus2Str(ret));
            res = false;
        }
    }
    return res;
}

bool rtc_internal_set(uint8_t num, const struct tm *const DateTime) {
    bool res = false;
    res = rtc_internal_set_time(num, DateTime);
    res = rtc_internal_set_date(num, DateTime) ;
    return res;
}
/*
#define RTC_MONTH_JANUARY              ((uint8_t)0x01)
#define RTC_MONTH_FEBRUARY             ((uint8_t)0x02)
#define RTC_MONTH_MARCH                ((uint8_t)0x03)
#define RTC_MONTH_APRIL                ((uint8_t)0x04)
#define RTC_MONTH_MAY                  ((uint8_t)0x05)
#define RTC_MONTH_JUNE                 ((uint8_t)0x06)
#define RTC_MONTH_JULY                 ((uint8_t)0x07)
#define RTC_MONTH_AUGUST               ((uint8_t)0x08)
#define RTC_MONTH_SEPTEMBER            ((uint8_t)0x09)
#define RTC_MONTH_OCTOBER              ((uint8_t)0x10)
#define RTC_MONTH_NOVEMBER             ((uint8_t)0x11)
#define RTC_MONTH_DECEMBER             ((uint8_t)0x12)
 * */
static int RtcHalMonthToMonth(const uint8_t hal_month) {
	int month = 15;
    switch(hal_month) {
        case 1: month = 0; break;
        case 2: month = 1; break;
        case 3: month = 2; break;
        case 4: month = 3; break;
        case 5: month = 4; break;
        case 6: month = 5; break;
        case 7: month = 6; break;
        case 8: month = 7; break;
        case 9: month = 8; break;
        case 10: month = 9; break;
        case 11: month = 10; break;
        case 12: month = 11; break;
        default:
        	LOG_ERROR(LG_RTC,"MothErr:%u,%u",hal_month,RTC_MONTH_DECEMBER);
        	month =11;break;
    }
    return month;
}



bool rtc_internal_get(uint8_t num, struct tm *const DateTime) {
    bool res = false;
    RtcHandle_t *Node = RtcGetNode(num);
    if(Node) {
        if(DateTime) {
            HAL_StatusTypeDef ret = HAL_ERROR;
            RTC_TimeTypeDef HalTime = {0};
            ret = HAL_RTC_GetTime(&Node->h_rtc, &HalTime, RTC_FORMAT_BIN);
            if(HAL_OK==ret) {
                RTC_DateTypeDef HalDate = {0};
                ret = HAL_RTC_GetDate(&Node->h_rtc, &HalDate, RTC_FORMAT_BIN);
                if (HAL_OK==ret) {
                      DateTime->tm_sec=HalTime.Seconds;//[0,60]
                      DateTime->tm_min=HalTime.Minutes;//[0,59]
                      DateTime->tm_hour=HalTime.Hours;//[0,23]
                      DateTime->tm_mday=HalDate.Date;//[1,31]
                      DateTime->tm_year=RTC_HAL_START_YEAR + HalDate.Year;// since 1900
                      DateTime->tm_wday=HalDate.WeekDay;//[0,6]
                      DateTime->tm_mon=RtcHalMonthToMonth(HalDate.Month);//[0,11]
                      DateTime->tm_yday=HalDate.Date+30*DateTime->tm_mon;//[0,365]
                      res = true;
                } else {
                    LOG_ERROR(LG_RTC,"Get,Date,Err:%s",HalStatus2Str(ret));
                    res = false;
                }
            }else {
                LOG_ERROR(LG_RTC,"Get,Time,Err:%s",HalStatus2Str(ret));
                res = false;
            }
        }else {
            LOG_ERROR(LG_RTC,"Time,Prt,Err");
            res = false;
        }
    }else {
        LOG_ERROR(LG_RTC,"Node,Err");
        res = false;
    }
    return res;
}

