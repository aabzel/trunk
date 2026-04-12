#ifndef DUMMY_MCU_H
#define DUMMY_MCU_H

#include <stdint.h>

#include "dummy_mcu_types.h"

#ifdef HAS_WRITER
#include "writer_types.h"
#endif

#ifdef HAS_CMSIS
#include "core_cm7.h"
#endif

#ifdef HAS_DIAG
#include "dummy_mcu_diag.h"
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

void some_fun(void) ;

#ifdef HAS_WRITER
WriterHandle_t* core_to_writer(int8_t core_num) ;
WriterHandle_t* multicore_get_writer(void);
#endif
void Core0_main(void);
void Core1_main(void);
void Core2_main(void);

#endif /* DUMMY_MCU_H */
