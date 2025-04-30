#ifndef U_BLOX_DRIVER_H
#define U_BLOX_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "timer_utils.h"
#ifdef HAS_CLOCK
#include "clocks.h"
#endif
#include "data_utils.h"
#include "gnss_utils.h"
#include "ubx_constants.h"
#include "ubx_protocol.h"

#if !defined(HAS_UART) && defined(HAS_MCU)
#error "Ublox driver requires UART driver"
#endif

#define UBX_PERIOD_US SEC_2_US(4)
#define UBX_SEND_TRY 15
#define UBX_SEND_TIME_OUT_MS 2000
#define UBX_RX_TIME_OUT_MS S_2_MS(15)

#ifdef HAS_UART1

#ifdef UART_NUM_ZED_F9P
#define UBX_UART_NUM UART_NUM_ZED_F9P
#else
#define UBX_UART_NUM 1
#endif /*UART_NUM_ZED_F9P*/

#endif /*HAS_UART1*/

#if 0
#define UBX_KEY_CNT 1
#endif
typedef struct xkeyValItem_t {
    uint32_t key_id;
    Type64Union_t u_value;
    SatConst_t satellite_constellation;
} keyValItem_t;
/*
typedef struct xVariable_t{
 char name[];
 AllTypeUnion_t u_value
 uint8_t type;
}Variable_t;
**/

/*Variables that matter for the application*/
typedef struct xNavInfo_t {
    struct tm date_time;
    GnssCoordinate_t coordinate;
    Wgs84Coordinate_t Wgs84Coordinate;
    GnssVelocity_t velocity;
    uint8_t id[5];
    int32_t hmsl;
    uint32_t h_acc;
    uint32_t v_acc;
    uint32_t survey_in_mean_position_acc_mm;
    uint32_t survey_in_observation_time;
    int32_t roll;
    int32_t pitch;
    int32_t heading;
    uint32_t acc_roll;
    uint32_t acc_pitch;
    uint32_t acc_heading;
    UbxReceiverMode_t BaseRxMode;
    uint32_t fixedPosAcc_mm; /* Fixed position 3D accuracy*/
    uint32_t svin_min_dur_s; /* Survey-in minimum duration in seconds*/
    GnssFixType_t FixType;
    double height_m; /*Height above mean sea level*/
    /*velocity*/
} NavInfo_t;

extern NavInfo_t NavInfo;

bool ubx_cfg_get_val(uint32_t key_id, uint8_t layers);
bool ubx_cfg_set_val(uint32_t key_id, uint8_t* val, uint16_t val_len, uint8_t layers);
bool ubx_driver_init(void);
bool ubx_proc(void);
bool ubx_proc_frame(UbloxProtocol_t* inst);
bool ubx_reset_to_dflt(void);
bool ubx_send_message(uint8_t class_num, uint8_t id, uint8_t* payload, uint16_t len);
bool ubx_send_message_ack(uint8_t class_num, uint8_t id, uint8_t* payload, uint16_t len);
bool ubx_set_rate(uint16_t meas_rate_ms, uint16_t time_ref);
#ifdef __cplusplus
}
#endif

#endif /* U_BLOX_DRIVER_H */
