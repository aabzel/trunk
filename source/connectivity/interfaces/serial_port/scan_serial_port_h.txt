#ifndef SCAN_SERIAL_PORT_H
#define SCAN_SERIAL_PORT_H

// https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>
#include <windows.h>

#ifdef HAS_MICROCONTROLLER
#warning That code only for desktop builds
#endif

#define DEDUG_RX_TEXT 0
#define MAX_COM_NUM 20
#define DEBUG_FINE_VI_REQ 0
#define DEBUG_SPOT_COM 0
#define DEBUG_FAILED_OPENS 0

#define MAX_NUM_COM_DEV 40U

typedef enum { UNDEF_DEVICE = 0 } deciceId_t;

typedef struct {
    char comPortName[30];
    char deviceName[30];
    bool isExistPort;
    bool isExistDevice;
    uint64_t serialNumber;
    uint16_t deviceID;
} xSerialConnection_t;

extern xSerialConnection_t deviceList[MAX_COM_NUM];
extern HANDLE hComm;

bool com_receive_remain(HANDLE hComm, uint32_t* outRealRxArrayLen);
bool init_serial(char* com_name, uint32_t baud_rate);
bool is_serial_known(uint64_t inSerial);
bool serial_init(void);
bool scan_serial(void);
bool print_device_list(void);
bool com_send_str(HANDLE hComm, char* txBuffer, uint32_t txBuffLen);
bool com_receive_str(HANDLE hComm, char* outRxArray, uint32_t capasityRxArray, uint32_t* outRealRxArrayLen);
bool com_receive_str_timeout(HANDLE hComm, char* outRxArray, uint32_t capasityRxArray, uint32_t* len,
                             uint32_t time_out_ms);
char* parse_product_name(char* inStr, uint16_t inStrLen);
const char* dev_id_name(deciceId_t deviceID);
uint16_t parse_product(char* inStr, uint16_t inStrLen);

#ifdef __cplusplus
}
#endif

#endif /* SCAN_SERIAL_PORT_H */
