#include "usb_serial.h"

#include "array_diag.h"
#include "code_generator.h"
#include "log.h"
#include "time_mcal.h"
#include "usb_device.h"
#include "usb_mcal.h"

#ifdef HAS_UBS_FS
#include "usbd_fs_cdc_if.h"
#endif

#ifdef HAS_UBS_HS
#include "usbd_hs_cdc_if.h"
#endif

/*can be called form ISR TODO rename to usb_serial_tx_next */
bool usb_serial_tx_next(const uint8_t num) {
    bool res = false;
    UsbHandle_t* Node = UsbGetNode(num);
    if(Node) {
        // uint32_t count = fifo_get_count(&Node->TxFifo);
        if(Node->init) {
            uint32_t outLen = 0;
            res = fifo_pull_array(&Node->TxFifo, Node->TxBuff, sizeof(Node->TxBuff), &outLen);
            if(res) {
                res = usb_serial_send(num, Node->TxBuff, outLen);
            }
        }
    }
    return res;
}

/*
   Data to send over USB IN endpoint are sent over CDC interface
   through this function.

   tx_data: Buffer of data to be sent
   size: Number of data to be sent (in bytes)
  */
bool usb_serial_send(uint8_t num, const uint8_t* const tx_data, const uint16_t size) {
    bool res = false;
    UsbHandle_t* Node = UsbGetNode(num);
    if(Node) {
        USBD_StatusTypeDef status = USBD_FAIL;
#ifdef HAS_UBS_FS
        status = CDC_Transmit_FS(tx_data, size);
#endif

#ifdef HAS_UBS_HS
        status = CDC_Transmit_HS(tx_data, size);
#endif
        res = usb_device_status_to_res(status);
        if(res) {
            Node->tx_in_progress = true;
            Node->tx_start_ms = time_get_ms32();
            Node->tx_done = false;
            // LOG_INFO(USB_SERIAL, "%u,TxData:%s",num,ArrayToStr(tx_data,size) );
        } else {
            // LOG_ERROR(USB_SERIAL, "%u,Status:%u=%s",num,status,UsbDeviceErrToStr(status) );
        }
    }
    return res;
}

bool usb_serial_proc_one(const uint8_t num) {
    bool res = false;
    LOG_PARN(USB_SERIAL, "Proc:%u", num);
    UsbHandle_t* Node = UsbGetNode(num);
    if(Node) {
        if(false == Node->tx_in_progress) {
            uint32_t cnt = fifo_get_count(&Node->TxFifo);
            if(cnt) {
                res = usb_serial_tx_next(num);
            }
        }
    }
    return res;
}

static bool UsbSerialIsValidConfig(const UsbConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->TxFifoArray) {
            LOG_ERROR(USB, "TxFifoArray,error");
            res = false;
        }

        ifn(0 < Config->tx_buff_size) {
            LOG_ERROR(USB, "TxFifoBuffSize,error");
            res = false;
        }
    }
    return res;
}

void usb_serial_puts(void* stream_ptr, const char* str, int32_t len) {
    UsbHandle_t* Node = UsbGetNode(1);
    if(Node) {
        if(str) {
            if(len) {
                fifo_push_array(&Node->TxFifo, (uint8_t*)str, (uint32_t)len);
                // usb_serial_send(1,(uint8_t* ) str, len);
                // usb_serial_tx_next(1);
            }
        }
    }
}

void usb_serial_putc(void* stream_ptr, char ch) {
    UsbHandle_t* Node = UsbGetNode(1);
    if(Node) {
        fifo_push(&Node->TxFifo, (uint8_t)ch);
        // usb_serial_send(1,(uint8_t*) &ch, 1);
        // usb_serial_tx_next(1);
    }
}

bool usb_serial_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Node = (WriterHandle_t*)base;
    if(Node) {
        strcpy((char*)Node->data, "");
        uint32_t out_len = 0;
        Node->in_transmit = 0;
        res = fifo_pull_array(&Node->fifo, Node->data, 200, &out_len);
        if(false == res) {
            Node->fifo.err_cnt++;
        } else {
            Node->in_transmit = out_len;
        }

        if(0 < Node->in_transmit) {
            Node->tx_cnt += Node->in_transmit;
            if(Node->enable) {
                UsbHandle_t* Usb = UsbGetNode(1);
                if(Usb) {
                    res = fifo_push_array(&Usb->TxFifo, (uint8_t*)Node->data, (uint32_t)Node->in_transmit);
                }
            }
            Node->in_transmit = 0;
        }
    }
    return res;
}

bool usb_serial_init_one(uint8_t num) {
    bool res = false;
    const UsbConfig_t* Config = UsbGetConfig(num);
    if(Config) {
        res = UsbSerialIsValidConfig(Config);
        if(res) {
            UsbHandle_t* Node = UsbGetNode(num);
            if(Node) {
                Node->init = true;
                Node->rx_len = 0;
                Node->tx_start_ms = 0;
                Node->tx_in_progress = false;
                memset(Node->TxBuff, 0, USB_SERIAL_TX_SIZE_MAX);
                memset(Node->RxData, 0, USB_SERIAL_RX_SIZE_MAX);
                res = fifo_init(&Node->TxFifo, Config->TxFifoArray, Config->tx_buff_size);
            }
        }
    }
    return res;
}
