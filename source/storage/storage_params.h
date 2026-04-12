#ifndef STORAGE_PARAMS_H
#define STORAGE_PARAMS_H

#include "storage_types.h"
#include "common_diag.h"

#ifdef HAS_DIAG
#define PARAM_STORAGE_BYTE_PARSER .parser = U8ToStr,
#define PARAM_STORAGE_WORD_PARSER .parser = U16ToStr,
#else
#define PARAM_STORAGE_BYTE_PARSER
#define PARAM_STORAGE_WORD_PARSER
#endif



#define PARAMS_STORAGE                                           \
    {                                                            \
      .facility = SYS,                                           \
      .id = PAR_ID_BYTE,                                         \
      .len = 1,                                                  \
      .type = TYPE_UINT8,                                        \
      .default_value = "0",                                      \
      .name = "byte",                                            \
      PARAM_STORAGE_BYTE_PARSER                                  \
     },                                                          \
    {                                                            \
      .facility = SYS,                                           \
      .id = PAR_ID_WORD,                                         \
      .len = 2,                                                  \
      .type = TYPE_UINT16,                                       \
      .default_value = "0",                                      \
      .name = "Word",                                            \
      PARAM_STORAGE_WORD_PARSER                                  \
     },

#endif /* STORAGE_PARAMS_H */
