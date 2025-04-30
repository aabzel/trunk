#ifndef PROTOCOLS_INIT_H
#define PROTOCOLS_INIT_H

#ifdef HAS_RDS
#include "rds_protocol.h"
#define RDS_INIT {.name="RDS", .init_function=rds_protocol_init,},
#else
#define RDS_INIT
#endif

#ifdef HAS_CLI
#include "cli_drv.h"
#define CLI_INIT {.name="CLI", .init_function=cli_mcal_init,},
#else
#define CLI_INIT
#endif

#ifdef HAS_NMEA
#include "nmea_protocol.h"
#define NMEA_INIT {.name="Nmea", .init_function=nmea_mcal_init,},
#else
#define NMEA_INIT
#endif

#ifdef HAS_TBFP
#include "tbfp.h"

#ifdef HAS_LOG
#define TBFP_INIT_NAME .name = "TBFP",
#else
#define TBFP_INIT_NAME
#endif

#define TBFP_INIT { .init_function = tbfp_mcal_init, TBFP_INIT_NAME },
#else
#define TBFP_INIT
#endif

#ifdef HAS_DS_TWR
#include "ds_twr.h"
#define DS_TWR_INIT {.name="DS_TWR", .init_function=ds_twr_init,},
#else
#define DS_TWR_INIT
#endif

#ifdef HAS_DECAWAVE
#include "decawave.h"
#define DECAWAVE_INIT {.name="DecaWave", .init_function=decawave_init,},
#else
#define DECAWAVE_INIT
#endif

#ifdef HAS_DECAWAVE_NATIVE
#include "decawave_native.h"
#define DECAWAVE_NATIVE_INIT {.name="DecaWaveNat", .init_function=decawave_native_init,},
#else
#define DECAWAVE_NATIVE_INIT
#endif

#ifdef HAS_ISO_TP
#include "iso_tp.h"
#define ISO_TP_INIT {.name="iso_tp", .init_function=iso_tp_mcal_init,},
#else
#define ISO_TP_INIT
#endif

#ifdef HAS_RTCM
#include "rtcm3.h"
#define RTCM_INIT {.name="RTCM3", .init_function=rtcm3_init,},
#else
#define RTCM_INIT
#endif

#ifdef HAS_UBX
#include "ubx_protocol.h"
#define UBX_INIT {.name="UBX", .init_function=ubx_init,},
#else
#define UBX_INIT
#endif

#ifdef HAS_UDS
#include "uds.h"
#define UDS_INIT {.name="UDS", .init_function=uds_mcal_init,}, \
                 {.name="DID", .init_function=did_mcal_init,},
#else
#define UDS_INIT
#endif

#ifdef HAS_STRING_READER
#include "string_reader.h"
#define STRING_READER_INIT {.name="StringReader", .init_function=string_reader_mcal_init,},
#else
#define STRING_READER_INIT
#endif


/*Order matters!*/
#define PROTOCOLS_INIT             \
    STRING_READER_INIT             \
    CLI_INIT                       \
    TBFP_INIT                      \
    DS_TWR_INIT                    \
    DECAWAVE_INIT                  \
    DECAWAVE_NATIVE_INIT           \
    RTCM_INIT                      \
    RDS_INIT                       \
    UBX_INIT                       \
    NMEA_INIT                      \
    ISO_TP_INIT                    \
    UDS_INIT

#endif /* PROTOCOLS_INIT_H */
