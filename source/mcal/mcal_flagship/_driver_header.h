#ifndef INCLUDE_DRIVER_HEADER_H_
#define INCLUDE_DRIVER_HEADER_H_

//#include "_device.h"
#ifdef HAS_CAN
#include "module_driver_flexcan.h"
#endif

#ifdef HAS_CLOCK
#include "module_driver_pcc.h"
#endif

#ifdef HAS_FC7300_SDK_V2_3_2
#ifdef HAS_FPU
#include "module_driver_fpu.h"
#endif
#endif

#ifdef HAS_GPIO
#include "module_driver_gpio.h"
#endif

#ifdef HAS_DMA
#include "module_driver_dma.h"
#endif


#ifdef HAS_ADC
#include "module_driver_adc.h"
#endif

#ifdef HAS_CLOCK
#include "module_driver_scg.h"
#endif

#ifdef HAS_UART
#include "module_driver_fcuart.h"
#endif

#if 0
#include "module_driver_csc.h"
#include "module_driver_ftu.h"
#include "module_driver_port.h"
#include "module_driver_systick.h"
#include "module_driver_fcpit.h"
#include "module_driver_trgsel.h"
#include "module_driver_ptimer.h"
#include "module_driver_fcspi.h"
#include "module_driver_mb.h"
#include "module_driver_hsm.h"
#include "module_driver_flash.h"

#include "module_driver_crc.h"
#include "module_driver_tstmp.h"
#endif


#endif /* INCLUDE_DRIVER_HEADER_H_ */
