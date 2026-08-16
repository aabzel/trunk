#include "serial_port.h"

#include <stdio.h>
#include <time.h>

#include <windows.h>

#include "code_generator.h"
#include "convert.h"
#include "log.h"
#include "str_utils.h"
#include "win_utils.h"
#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_SLCAN
#include "slcan.h"
#endif

#include "none_blocking_pause.h"

COMPONENT_GET_NODE(SerialPort, serial_port)
COMPONENT_GET_CONFIG(SerialPort, serial_port)

static bool SerialPortIsValidConfig(const SerialPortConfig_t* Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(0 < Config->bit_rate) {
            LOG_ERROR(SERIAL_PORT, "SERIAL_PORT_%u,bit_rate,Err", Config->num);
            res = false;
        }

        ifn(Config->name) { LOG_WARNING(SERIAL_PORT, "SERIAL_PORT_%u,Name,Err", Config->num); }

        ifn(Config->com_port_num) { LOG_WARNING(SERIAL_PORT, "SERIAL_PORT_%u,Name,Err", Config->num); }

        ifn(0 < Config->byte_tx_pause_ms) { LOG_WARNING(SERIAL_PORT, "SERIAL_PORT_%u,bit_rate,Err", Config->num); }
    }
    return res;
}

SerialPortHandle_t* SerialPortNumToNode(uint8_t com_port_num) {
    SerialPortHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = serial_port_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(com_port_num == SerialPortInstance[i].com_port_num) {
            if(SerialPortInstance[i].valid) {
                Node = &SerialPortInstance[i];
                break;
            }
        }
    }
    return Node;
}

/*
 * COMport num to logic serial_num
 *
 * */
uint8_t serial_port_com_to_num(const uint8_t com_port_num) {
    uint8_t serial_num = 0;
    uint32_t i = 0;
    uint32_t cnt = serial_port_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(com_port_num == SerialPortInstance[i].com_port_num) {
            if(SerialPortInstance[i].valid) {
                serial_num = SerialPortInstance[i].num;
                break;
            }
        }
    }
    return serial_num;
}

uint8_t serial_num_to_port_com(const uint8_t num) {
    uint8_t port_com = 0;
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {
        port_com = Node->com_port_num;
    }
    return port_com;
}

bool serial_port_check(uint8_t num) {
    bool res = false;
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {

        if(Node->hComm) {
            LOG_WARNING(SERIAL_PORT, "Close,hComm:0x%p", Node->hComm);
            BOOL ret = 0;
            (void)ret;
            ret = CloseHandle(Node->hComm);
            res = true;
        }

        char ComPortName[80] = {0};
        snprintf(ComPortName, sizeof(ComPortName), "COM%u", num);
        LOG_PARN(SERIAL_PORT, "TryOpen:%s...", ComPortName);
        Node->hComm = CreateFile(ComPortName,
                                 GENERIC_READ,  // Read
                                 0,             // No Sharing
                                 NULL,          // No Security
                                 OPEN_EXISTING, // Open existing port only
                                 0,             // Non Overlapped I/O
                                 NULL);         // Null for Comm Devices
        if(INVALID_HANDLE_VALUE == Node->hComm) {
            LOG_PARN(SERIAL_PORT, "%s,OpenErr", ComPortName);
            res = false;
        } else {
            LOG_PARN(SERIAL_PORT, "Open,%s,OK", ComPortName);
            BOOL ret = CloseHandle(Node->hComm);
            (void)ret;
            res = true;
        }
    }
    return res;
}

bool serial_port_scan_ports(void) {
    bool res = false;
    LOG_WARNING(SERIAL_PORT, "Scan...");
    uint32_t ok_cnt = 0;
    uint32_t i = 0;
    for(i = 0; i < SERIAL_PORT_MAX_CNT; i++) {
        res = serial_port_check(i);
        if(res) {
            LOG_INFO(SERIAL_PORT, "Open,COM%u,OK", i);
        }
        ok_cnt = ok_cnt_update(ok_cnt, res);
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

bool serial_port_init_custom(void) {
    bool res = true;
    LOG_INFO(SERIAL_PORT, "Version:%u", SERIAL_PORT_VERSION);
    log_level_t log_l = log_level_get(SERIAL_PORT);
    if(log_l <= LOG_LEVEL_INFO) {
        res = serial_port_scan();
    }
    return res;
}

bool serial_port_proc_one(uint8_t num) {
    bool res = false;
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {
        LOG_PARN(SERIAL_PORT, "SERIAL_PORT_%u,Proc", num);
        res = true;
        bool loopRun = true;
#ifdef HAS_TBFP
        InterfaceType_t if_serial = {
            .interface_name = INTERFACE_NAME_SERIAL_PORT,
            .num = 0,
        };
        TbfpHandle_t* Tbfp = TbfpInterfaceToNode(if_serial);
        if(Tbfp) {
        } else {
            LOG_ERROR(SERIAL_PORT, "NoTbfp for if %u", if_serial.word);
        }
#endif

#ifdef HAS_SLCAN
        SlCanHandle_t* SlCan = SlCanComNumToNode(Node->com_port_num);
        if(SlCan) {
        } else {
            LOG_ERROR(SERIAL_PORT, "NoSlCanFor,COM%u", Node->com_port_num);
        }
#endif
        while(loopRun) {
            DWORD rx_size_cnt;
            rx_size_cnt = 0;
            char rx_byte = ' ';
            ReadFile(Node->hComm,     // Handle of the Serial port
                     &rx_byte,        // Temporary character
                     sizeof(rx_byte), // Size of TempChar
                     &rx_size_cnt,    // Number of bytes read
                     NULL);
            if(1 == rx_size_cnt) {
                LOG_DEBUG(SERIAL_PORT, "COM%u,Rx:[%u]=0x%02x", Node->com_port_num, Node->rx_cnt, rx_byte);
                Node->rx_cnt++;
                loopRun = true;
#ifdef HAS_TBFP
                if(Tbfp) {
                    res = tbfp_proc_byte(Tbfp, (uint8_t)rx_byte);
                } else {
                    LOG_ERROR(SERIAL_PORT, "NoTbfp for if %u", if_serial.word);
                }
#endif

#ifdef HAS_SLCAN
                if(SlCan) {
                    res = slcan_proc_byte(SlCan, (uint8_t)rx_byte);
                } else {
                    LOG_ERROR(SERIAL_PORT, "NoSlCanForIf1");
                }
#endif

            } else {
                loopRun = false;
            }
        };
    }
    return res;
}

static bool serial_port_send_pause(SerialPortHandle_t* const Node, uint8_t* data, uint32_t size) {
    bool res = false;
    if(data) {
        if(size) {
            uint32_t i = 0;
            uint32_t ok_cnt = 0;
            for(i = 0; i < size; i++) {
                LOG_PARN(SERIAL_PORT, "COM%u,Tx[%u]=0x%02x", Node->com_port_num, Node->tx_cnt, data[i]);
                BOOL status = 0;
                DWORD written = 0;
                res = false;
                status = WriteFile(Node->hComm, &data[i], (DWORD)1, &written, NULL);
                if(status) {
                    if(1 == written) {
                        Node->tx_cnt++;
                        ok_cnt++;
                        res = true;
                    }
                }

                if(!res) {
                    DWORD last_error = GetLastError();
                    LOG_ERROR(SERIAL_PORT, "hComm:0x%p,%u/%u,LastError:0x%x=%s", Node->hComm, i, size, last_error,
                              SerialPortErrorToStr(last_error));
                    serial_port_init_one(Node->num);
                }
                wait_ms(Node->byte_tx_pause_ms);
            }

            if(ok_cnt == size) {
                LOG_PARN(SERIAL_PORT, "Write:0x%p,Ok", Node->hComm);
                res = true;
            } else {
                res = false;
                LOG_ERROR(SERIAL_PORT, "WriteSerialErr:%u/%u", ok_cnt, size);
            }
        } else {
            LOG_ERROR(SERIAL_PORT, "SizeErr");
        }
    } else {
        LOG_ERROR(SERIAL_PORT, "DataErr");
    }

    return res;
}

bool serial_port_send(uint8_t com_num, uint8_t* data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SERIAL_PORT, "COM%u,Send:[%s]", com_num, data);
    SerialPortHandle_t* Node = SerialPortNumToNode(com_num);
    if(Node) {
        LOG_DEBUG(SERIAL_PORT, "Send,%s", SerialPortNodeToStr(Node));
        res = serial_port_send_pause(Node, data, size);
        log_parn_res(SERIAL_PORT, res, "SendPause");
    } else {
        LOG_ERROR(SERIAL_PORT, "NoCOM%u", com_num);
    }
    return res;
}

static bool serial_port_set_params(HANDLE hComm, uint32_t baud_rate) {
    bool res = false;
    // Initializing DCB structure
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    BOOL status = GetCommState(hComm, &dcbSerialParams);
    dcbSerialParams.BaudRate = baud_rate;  // Setting BaudRate = 460800
    dcbSerialParams.ByteSize = 8;          // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT; // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;     // Setting Parity = None

    SetCommState(hComm, &dcbSerialParams);
    if(status) {
        res = true;
    }
    return res;
}

static bool serial_port_set_timeout(HANDLE hComm) {
    bool res = false;
    COMMTIMEOUTS SerailPortTimeOuts = {0};
    SerailPortTimeOuts.ReadIntervalTimeout = 2;        // in milliseconds
    SerailPortTimeOuts.ReadTotalTimeoutMultiplier = 3; //
    SerailPortTimeOuts.ReadTotalTimeoutConstant = 10;  // in milliseconds
    SerailPortTimeOuts.WriteTotalTimeoutConstant = 1;  // in milliseconds
    SerailPortTimeOuts.WriteTotalTimeoutMultiplier = 1;

    SetCommTimeouts(hComm, &SerailPortTimeOuts);
    return res;
}

static bool serial_port_init_common(const SerialPortConfig_t* const Config, SerialPortHandle_t* const Node) {
    bool res = false;
    if(Config) {
        Node->num = Config->num;
        Node->byte_tx_pause_ms = Config->byte_tx_pause_ms;
        Node->com_port_num = Config->com_port_num;
        Node->bit_rate = Config->bit_rate;
        Node->valid = true;
        res = true;
    }
    return res;
}

bool serial_port_close(uint8_t com_port_num) {
    bool res = false;
    uint8_t num = serial_port_com_to_num(com_port_num);
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {
        if(Node->hComm) {
            LOG_WARNING(SERIAL_PORT, "Close %p", Node->hComm);
            BOOL ret = 0;
            (void)ret;
            ret = CloseHandle(Node->hComm);
            res = true;
        }
    }
    return res;
}

bool serial_port_re_init_one(const uint8_t num, const uint8_t com_port_num, const uint32_t bit_rate,
                             const uint32_t byte_tx_pause_ms) {
    bool res = false;
    LOG_WARNING(SERIAL_PORT, "Init:%u,COM%u,BitRate:%u bit/s", num, com_port_num, bit_rate);
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {
        Node->com_port_num = com_port_num;
        Node->bit_rate = bit_rate;
        Node->byte_tx_pause_ms = byte_tx_pause_ms;
        res = true;

        if(((void*)0xFFFFFFFF) != Node->hComm) {
            LOG_WARNING(SERIAL_PORT, "Close:0x%p", Node->hComm);
            BOOL ret = 0;
            (void)ret;
            ret = CloseHandle(Node->hComm);
        }

        char ComPortName[80] = {0};
        snprintf(ComPortName, sizeof(ComPortName), "COM%u", Node->com_port_num);
        LOG_WARNING(SERIAL_PORT, "TryOpen:[%s].", ComPortName);
        Node->hComm = CreateFile(ComPortName,
                                 GENERIC_READ | GENERIC_WRITE, // Read/Write
                                 0,                            // No Sharing
                                 NULL,                         // No Security
                                 OPEN_EXISTING,                // Open existing port only OPEN_ALWAYS
                                 0,                            // Non Overlapped I/O
                                 NULL);                        // Null for Comm Devices
        if(INVALID_HANDLE_VALUE == Node->hComm) {
            LOG_ERROR(SERIAL_PORT, "OpenErr,%s", SerialPortNodeToStr(Node));
            res = false;
        } else {
            serial_port_set_params(Node->hComm, bit_rate);
            serial_port_set_timeout(Node->hComm);
            res = true;
            LOG_INFO(SERIAL_PORT, "OpenOk,%s", SerialPortNodeToStr(Node));
        }
        LOG_INFO(SERIAL_PORT, "init:%u Ok", num);
    } else {
        LOG_ERROR(SERIAL_PORT, "NodeErr %u", num);
    }

    return res;
}

bool serial_port_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SERIAL_PORT, "init:%u", num);
    const SerialPortConfig_t* Config = SerialPortGetConfig(num);
    if(Config) {
        res = SerialPortIsValidConfig(Config);
        if(res) {
            LOG_WARNING(SERIAL_PORT, "%s", SerialPortConfigToStr(Config));
            SerialPortHandle_t* Node = SerialPortGetNode(num);
            if(Node) {
                res = serial_port_init_common(Config, Node);
                /* Default COM port not always valid */
                serial_port_re_init_one(num, Node->com_port_num, Config->bit_rate, Node->byte_tx_pause_ms);
            } else {
                LOG_ERROR(SERIAL_PORT, "SERIAL_PORT_%u,NodeErr", num);
            }
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(SERIAL_PORT, SERIAL_PORT, serial_port)
COMPONENT_PROC_PATTERT(SERIAL_PORT, SERIAL_PORT, serial_port)
