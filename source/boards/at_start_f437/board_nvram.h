#ifndef BOARD_NVRAM_H
#define BOARD_NVRAM_H

#define NVRAM_IDS_BOARD    \
    NVRAM_ID_SERIAL_NUM=25,

#define NVRAM_BOARD                               \
    {                                             \
      .id = NVRAM_ID_SERIAL_NUM,                  \
      .len = 4,                                   \
      .eepromAddress = 0x7,                       \
      .type = STORAGE_TYPE_UINT32,                \
      .defaultValue = "0",                        \
      .name = "SerialNum"                         \
    },


#endif /* BOARD_NVRAM_H  */
