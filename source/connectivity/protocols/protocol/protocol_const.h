#ifndef PROTOCOL_GENERAL_H
#define PROTOCOL_GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WAIT_INIT = 0,
    WAIT_PREAMBLE = 1,
    WAIT_FLAGS = 2,
    WAIT_SERIAL_NUM = 3,
    WAIT_LEN = 4,
    WAIT_FRAME_ID = 5,
    WAIT_PAYLOAD = 7,
    WAIT_CRC = 8,
    WAIT_RETX_CNT = 9,
    WAIT_UNDEF = 10,
    RX_DONE = 11,
} RxState_t;

typedef enum {
	PROTO_STACK_FRAME=1,
	PROTO_AT_COMMANDS=2,
	PROTO_BASE64=3,
	PROTO_BASE16=4,
	PROTO_CLI=5,
	PROTO_CSV=6,
	PROTO_DECAWAVE=7,
	PROTO_DS_TWR=8,
	PROTO_NMEA=9,
	PROTO_RDS=10,
	PROTO_RTCM3=11,
	PROTO_TBFP=12,
	PROTO_UBX=13,

	PROTO_UNDEF=0,
}Protocol_t;

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_GENERAL_H */
