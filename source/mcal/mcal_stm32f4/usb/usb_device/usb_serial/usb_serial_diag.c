#include "usb_serial_diag.h"

#include "usbd_cdc.h"

bool usb_serial_diag(void){
    bool res = false;
    return res;
}


    /*******************************************************************************/
    /* Line Coding Structure                                                       */
    /*-----------------------------------------------------------------------------*/
    /* Offset | Field       | Size | Value  | Description                          */
    /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
    /* 4      | bCharFormat |   1  | Number | Stop bits                            */
    /*                                        0 - 1 Stop bit                       */
    /*                                        1 - 1.5 Stop bits                    */
    /*                                        2 - 2 Stop bits                      */
    /* 5      | bParityType |  1   | Number | Parity                               */
    /*                                        0 - None                             */
    /*                                        1 - Odd                              */
    /*                                        2 - Even                             */
    /*                                        3 - Mark                             */
    /*                                        4 - Space                            */
    /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
    /*******************************************************************************/
const char* UsbSerialCdcCmdToStr(const uint8_t cmd) {
    char *name = "?";
    switch (cmd) {
        case CDC_SEND_ENCAPSULATED_COMMAND:
            name = "SEND_Encapsulated_CMD";
            break;
        case CDC_GET_ENCAPSULATED_RESPONSE:
            name = "GetEncapsulated_RESP";
            break;
        case CDC_SET_COMM_FEATURE:
            name = "SetComm_FEATURE";
            break;
        case CDC_GET_COMM_FEATURE:
            name = "GetComm_FEATURE";
            break;
        case CDC_CLEAR_COMM_FEATURE:
            name = "Clear_Comm_FEATURE";
            break;
        case CDC_SET_LINE_CODING:
            name = "SetLine_CODING";
            break;
        case CDC_GET_LINE_CODING:
            name = "GetLine_CODING";
            break;
        case CDC_SET_CONTROL_LINE_STATE:
            name = "Set_Ctrl_Line_STATE";
            break;
        case CDC_SEND_BREAK:
            name = "SendBreak";
            break;
        default:
            name = "?";
            break;
    }
    return name;
}

