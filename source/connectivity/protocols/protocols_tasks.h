#ifndef PROTOCOLS_TASKS_H
#define PROTOCOLS_TASKS_H

#ifdef HAS_UBX_PROC
#include "ubx.h"
#define UBX_TASK {.name="UBX", .period_us=UBX_PERIOD_US, .limiter.function=ubx_proc,},
#else
#define UBX_TASK
#endif

#ifdef HAS_ISO_TP_PROC
#include "iso_tp_mcal.h"
#define ISO_TP_TASK {.name = "IsoTp", .period_us = ISO_TP_PERIOD_US, .limiter.function = iso_tp_proc,},
#else
#define ISO_TP_TASK
#endif

#ifdef HAS_RDS_PROC
#include "rds.h"
#define RDS_TASK {.name="RDS", .period_us=RDS_PERIOD_US, .limiter.function=ubx_proc,},
#else
#define RDS_TASK
#endif

#ifdef HAS_CLI_PROC
#include "cli_drv.h"
#define CLI_TASK  {.name="CLI", .period_us=CLI_PERIOD_US, .limiter.function=cli_proc,},
#else
#define CLI_TASK
#endif

#ifdef HAS_TBFP_PROC
#include "tbfp.h"

#ifdef HAS_LOG
#define TBFP_TASK_NAME .name = "Tbfp"
#define TBFP_HEARTBEAT_TASK_NAME .name = "TbfpHB"
#else
#define TBFP_TASK_NAME
#define TBFP_HEARTBEAT_TASK_NAME
#endif

#ifdef HAS_TBFP_EXT
#define TBFP_HEARTBEAT_TASK     \
   { .period_us = TBFP_HEARTBEAT_PERIOD_US, \
	 .limiter.function = tbfp_heartbeat_proc, TBFP_HEARTBEAT_TASK_NAME \
   },
#else
#define TBFP_HEARTBEAT_TASK
#endif


#define TBFP_TASK  TBFP_HEARTBEAT_TASK  \
    { .period_us=TBFP_PERIOD_US, .limiter.function=tbfp_proc, TBFP_TASK_NAME},
#else
#define TBFP_TASK
#endif

#ifdef HAS_DS_TWR_PROC
#include "ds_twr.h"
#define DS_TWR_TASK {.name="DS_TWR", .period_us=DS_TWR_PERIOD_US, .limiter.function=ds_twr_proc,},
#else
#define DS_TWR_TASK
#endif

#ifdef HAS_NMEA_PROC
#include "nmea_protocol.h"
#define NMEA_TASKS                                                                  \
    {.name="NMEA",     .period_us=NMEA_PERIOD_US, .limiter.function=nmea_proc,},    \
    {.name="NmeaRtc",  .period_us=NMEA_SYNC_RTC_PERIOD_US, .limiter.function=nmea_sync_rtc_proc,}, \
    {.name="NmeaLog",  .period_us=NMEA_LOG_RTC_PERIOD_US, .limiter.function=nmea_log_proc,},
#else
#define NMEA_TASKS
#endif

#ifdef HAS_IR_SAMSUNG_PROC
#include "ir_samsung_mcal.h"
#define IR_SAMSUNG_TASK {.name="IrSamsung", .period_us=IR_SAMSUNG_PERIOD_US, .limiter.function=ir_samsung_proc,},
#else
#define IR_SAMSUNG_TASK
#endif

#ifdef HAS_PCAN_PROC
#include "pcan_mcal.h"
#define PCAN_TASK {.name="pCan", .period_us=PCAN_PERIOD_US, .limiter.function = pcan_proc, },
#else
#define PCAN_TASK
#endif

#ifdef HAS_UDS_PROC
#include "uds.h"
#define UDS_TASK {.name="UDS",     .period_us=UDS_PERIOD_US, .limiter.function=uds_proc,}, \
                 {.name="UDS_DID", .period_us=DID_PERIOD_US, .limiter.function=did_proc,},
#else
#define UDS_TASK
#endif

#ifdef HAS_SLCAN_PROC
#include "slcan.h"
#define SLCAN_TASK                   \
    {.name = "SLCAN", .period_us = SLCAN_PERIOD_US, .limiter.function = slcan_proc,},
#else
#define SLCAN_TASK
#endif

#ifdef HAS_STRING_READER_PROC
#include "string_reader.h"
#define STRING_READER_TASK     {.name="StringReader",                   \
                                .period_us=STRING_READER_PERIOD_US,     \
                                .limiter.function=string_reader_proc,},
#else
#define STRING_READER_TASK
#endif

#ifdef HAS_UDS_CLIENT_PROC
#include "uds_client_mcal.h"
#define UDS_CLIENT_TP_TASK  {                                                 \
                         .name = "UdsTesterPresent",                          \
                         .period_us = UDS_CLIENT_TESTER_PRESENT_PERIOD_US,    \
                         .limiter.function = uds_client_tester_present_proc,  \
                        },

#define UDS_CLIENT_TASK {                                                     \
                         .name = "UdsClient",                                 \
                         .period_us = UDS_CLIENT_PERIOD_US,                   \
                         .limiter.function = uds_client_proc,                 \
                        },                                                    \

#else
#define UDS_CLIENT_TASK
#endif

#define PROTOCOlS_WIRELESS_TASKS   \
    RDS_TASK                       \
    DS_TWR_TASK                    \
    IR_SAMSUNG_TASK

#define PROTOCOlS_TASKS            \
    PROTOCOlS_WIRELESS_TASKS       \
    CLI_TASK                       \
    ISO_TP_TASK                    \
    TBFP_TASK                      \
    PCAN_TASK                      \
    NMEA_TASKS                     \
    SLCAN_TASK                     \
    STRING_READER_TASK             \
    UBX_TASK                       \
    UDS_TASK

#endif /* PROTOCOLS_TASKS_H */
