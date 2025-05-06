#include "serial_port.h"

#include <stdio.h>
#include <time.h>

#include <windows.h>

#include "code_generator.h"
#include "convert.h"
#include "log.h"
#include "str_utils.h"
#include "win_utils.h"
#include "none_blocking_pause.h"

COMPONENT_GET_NODE(SerialPort, serial_port)
COMPONENT_GET_CONFIG(SerialPort, serial_port)

bool serial_port_init_custom(void) {
    bool res = false;
    return res;
}

bool serial_port_proc_one(uint8_t num) {
    bool res = false;
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {
        res = true;
        char rx_byte;
        bool loopRun = true;
        DWORD rx_size_cnt;
        while(loopRun) {
            rx_size_cnt = 0;
            ReadFile(Node->hComm,     // Handle of the Serial port
                     &rx_byte,        // Temporary character
                     sizeof(rx_byte), // Size of TempChar
                     &rx_size_cnt,    // Number of bytes read
                     NULL);
            if(0 < rx_size_cnt) {
                LOG_DEBUG(SERIAL_PORT, "Rx:%u,0x%x=[%c]", num, rx_byte, rx_byte);
                loopRun = true;
            } else {
                loopRun = false;
            }
            Node->rx_cnt += rx_size_cnt;
        };
    }
    return res;
}

static bool serial_port_send_pause(SerialPortHandle_t* const Node, uint8_t* data, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    for(i=0;i<size;i++) {
        BOOL status;
        DWORD written = 0;
        status = WriteFile(Node->hComm, &data[i], (DWORD)1, &written, NULL);
        if(1==written) {
            if(status) {
            	Node->tx_cnt++;
            	ok_cnt++;
            }
        }
        wait_ms(Node->byte_tx_pause_ms);

    }

    if(ok_cnt==size) {
        LOG_DEBUG(SERIAL_PORT, "Write:%p,Ok[%s]", Node->hComm, data);
    	res = true;
    }else{
    	res = false;
        LOG_ERROR(SERIAL_PORT, "WriteSerialErr %u/%u", ok_cnt,size);
    }

    return res;
}


bool serial_port_send(uint8_t num, uint8_t* data, uint32_t size) {
    bool res = false;
    SerialPortHandle_t* Node = SerialPortGetNode(num);
    if(Node) {
        LOG_DEBUG(SERIAL_PORT, "Send,%s", SerialPortNodeToStr(Node));
        res = serial_port_send_pause(Node, data, size);
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

static bool serial_port_init_common(const SerialPortConfig_t* const Config,
		                            SerialPortHandle_t* const Node) {
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

bool serial_port_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SERIAL_PORT, "init:%u", num);
    const SerialPortConfig_t* Config = SerialPortGetConfig(num);
    if(Config) {
        LOG_WARNING(SERIAL_PORT, "%s", SerialPortConfigToStr(Config));
        SerialPortHandle_t* Node = SerialPortGetNode(num);
        if(Node) {
        	res = serial_port_init_common(Config, Node);


            res = true;
            char ComPortName[80] = {0};
            snprintf(ComPortName, sizeof(ComPortName), "COM%u", Config->com_port_num);
            LOG_WARNING(SERIAL_PORT, "TryOpen...");
            Node->hComm = CreateFile(ComPortName,
                                     GENERIC_READ | GENERIC_WRITE, // Read/Write
                                     0,                            // No Sharing
                                     NULL,                         // No Security
                                     OPEN_EXISTING,                // Open existing port only
                                     0,                            // Non Overlapped I/O
                                     NULL);                        // Null for Comm Devices
            if(INVALID_HANDLE_VALUE == Node->hComm) {
                LOG_ERROR(SERIAL_PORT, "OpenErr,%s", SerialPortNodeToStr(Node));
                res = false;
            } else {
                serial_port_set_params(Node->hComm, Config->bit_rate);
                serial_port_set_timeout(Node->hComm);
                res = true;
                LOG_INFO(SERIAL_PORT, "OpenOk,%s", SerialPortNodeToStr(Node));
            }

            LOG_INFO(SERIAL_PORT, "init:%u Ok", num);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(SERIAL_PORT, SERIAL_PORT, serial_port)
COMPONENT_PROC_PATTERT(SERIAL_PORT, SERIAL_PORT, serial_port)
