#include "rtc_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "artery_at32f4xx.h"

RTC_HandleTypeDef hrtc;

bool rtc_init(void) {
  bool res = false;
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)  {
      res = false;
  }else{
	  res = true;  
  }
  return res;
}


void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle){
  if(rtcHandle->Instance==RTC)  {
    __HAL_RCC_RTC_ENABLE();
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle){
  if(rtcHandle->Instance==RTC)  {
    __HAL_RCC_RTC_DISABLE();
  }
}

