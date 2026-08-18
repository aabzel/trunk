#ifndef RTK_PARAMS_H
#define RTK_PARAMS_H

#include "param_ids.h"
#include "param_types.h"

#define PARAMS_RTK                                                                   \
    {RTK, PAR_ID_BASE_LOCATION, 16, TYPE_STRUCT, "BaseLocat"},                            \
    {RTK, PAR_ID_RTK_FIX_LONG, 4, TYPE_UINT32, "FTKFixedTime"}, /*RTK fixed max duration*/\
    {RTK, PAR_ID_BASE_ACC, 4, TYPE_UINT32, "BaseAcc"},                                    \
    {RTK, PAR_ID_GPS, 1, TYPE_BOOL, "GpsCor"},                                            \
    {RTK, PAR_ID_GLONASS, 1, TYPE_BOOL, "GlnCor"},                                    \
    {RTK, PAR_ID_GALILEO, 1, TYPE_BOOL, "GalCor"},                                    \
    {RTK, PAR_ID_BEI_DOU, 1, TYPE_BOOL, "BeiCor"},                                     \
    {RTK, PAR_ID_RTK_CHANNEL, 1, TYPE_UINT8, "RTKchannel"},                               \
    {RTK, PAR_ID_GNSS_PERIOD, 2, TYPE_UINT16, "GnssPer"},                                 \
    {RTK, PAR_ID_BASE_ALT, 8, TYPE_DOUBLE, "BaseAlt"},

#endif /* RTK_PARAMS_H  */
