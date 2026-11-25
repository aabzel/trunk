#ifndef FC7300F8MDT_H
#define FC7300F8MDT_H

#include <stdint.h>

#include "v_def.h"
#include "fc7300f8mdt_types.h"
#include "FC7300F8MDT_rgm_common_feature.h"
#include "FC7300F8MDT_core_common_feature.h"

#ifdef HAS_WRITER
#include "writer_types.h"
#endif

#ifdef HAS_CMSIS
#include "core_cm7.h"
#endif

#ifdef HAS_DIAG
#include "fc7300f8mdt_diag.h"
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#include "device_header.h"

#ifdef HAS_WRITER
WriterHandle_t* core_to_writer(int8_t core_num) ;
WriterHandle_t* multicore_get_writer(void);
#endif
void Core0_main(void);
void Core1_main(void);
void Core2_main(void);

#endif /* FC7300F8MDT_H */
