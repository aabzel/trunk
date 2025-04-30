#ifndef EEPROM_DEP_H
#define EEPROM_DEP_H



#ifndef HAS_ARRAY
#warning "+ HAS_ARRAY"
#endif

#ifndef HAS_CRC16
#warning "+ HAS_CRC16"
#endif

#ifndef HAS_STORAGE
#warning "+ HAS_STORAGE"
#endif

#ifndef HAS_EEPROM
#error "+ HAS_EEPROM"
#endif

#ifndef HAS_TIME
#error "+ HAS_TIME"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+ HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#endif /* EEPROM_DEP_H */
