#include "adc_config.h"

#include "adc_drv.h"

#ifdef DeviceFamily_CC26X2
#include <rom.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCCC26XX.h>
#endif
#include "sys_config.h"

const ADCItem_t AdcItemsLUT[ADC_ITEMS_CNT] = {
    /* adc_channel        aux_pin    io_pin         pin   scale*/
    {0xFF, 0xff, 0xFF, 0xff, 999.99f},
};

