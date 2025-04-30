/*
 * def.h
 *
 *  Created on: 2020. 3. 20.
 *      Author: Baram
 */

#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#include "def_err.h"



#define _DEF_LED1                   0
#define _DEF_LED2                   1
#define _DEF_LED3                   2
#define _DEF_LED4                   3


#define _DEF_UART1                  0
#define _DEF_UART2                  1
#define _DEF_UART3                  2
#define _DEF_UART4                  3


#define _DEF_HIGH                   1
#define _DEF_LOW                    0



#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef map
#define map(value, in_min, in_max, out_min, out_max) ((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#endif



typedef struct
{
  uint8_t boot_name[32];
  uint8_t boot_ver[32];
  uint32_t magic_number;
  uint32_t addr_fw;
  uint32_t image_start;
  uint32_t image_end;
  uint32_t image_size;
} boot_tag_t;


typedef struct
{
  uint32_t magic_number;

  //-- fw info
  //
  uint8_t  version_str[32];
  uint8_t  board_str  [32];
  uint8_t  name_str   [32];
  uint8_t  date_str   [32];
  uint8_t  time_str   [32];
  uint32_t addr_tag;
  uint32_t addr_fw;

  uint32_t load_start;
  uint32_t load_size;
  uint32_t reserved   [30];

  //-- tag info
  //
  uint32_t tag_flash_type;
  uint32_t tag_flash_start;
  uint32_t tag_flash_end;
  uint32_t tag_flash_length;
  uint32_t tag_flash_crc;
  uint32_t tag_length;
  uint8_t  tag_date_str[32];
  uint8_t  tag_time_str[32];
} flash_tag_t;


#define FLASH_MAGIC_NUMBER      0x5555AAAA



#endif /* SRC_COMMON_DEF_H_ */
