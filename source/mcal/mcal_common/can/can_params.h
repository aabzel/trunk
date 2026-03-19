#ifndef CAN_PARAMS_H
#define CAN_PARAMS_H

#include "storage_types.h"
#include "common_diag.h"
#ifdef HAS_CAN_CUSTOM
#include "can_custom_params.h"
#endif

#define PARAMS_CAN                                    \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN0_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can0BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN1_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can1BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN2_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can2BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN3_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can3BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN4_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can4BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN5_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can5BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN6_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can6BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN7_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can7BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN8_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can8BitRate",                            \
    .parser = U32DecToStr,                            \
    },                                                \
    {                                                 \
    .facility = CAN,                                  \
    .id = PAR_ID_CAN9_BITRATE_HZ,                     \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "500000",                        \
    .name = "Can9BitRate",                            \
    .parser = U32DecToStr,                            \
    },

#endif /* CAN_PARAMS_H */
