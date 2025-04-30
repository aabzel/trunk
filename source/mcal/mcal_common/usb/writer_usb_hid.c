#include "writer_usb_hid.h"

#include <stdbool.h>
#include <string.h>

#ifndef HAS_HID
#error "Add HAS_HID"
#endif

#ifndef HAS_USB_DEVICE
#error "Add HAS_USB_DEVICE"
#endif

#include "usb_device.h"
#include "writer_generic.h"

#define MAX_USB_HID_BLOCK 100U

bool usb_hid_writer_transmit(struct generic_writer_s* writer) {
    bool res = false;
    static char data[300] = ""; /*TODO Determine min size*/
    if(writer) {
        res = fifo_pull_array(&writer->fifo, data, sizeof(data), (uint16_t*)&writer->in_transmit);
        if(false == res) {
            writer->fifo.err_cnt++;
        }
        if(0 < writer->in_transmit) {
            writer->tx_cnt += writer->in_transmit;
            if(MAX_USB_HID_BLOCK < writer->in_transmit) {
                writer->in_transmit = MAX_USB_HID_BLOCK;
            }
            if(writer->enable) {
                res = usb_key_board_send_array((uint8_t*)data, writer->in_transmit, key_insert_timeout_ms);
            }
        }
    }
    return res;
}

static char usb_hid_o_data[USB_HID_TX_ARRAY_SIZE] = {0};
generic_writer_t usb_hid_o = {
    .stream = {.f_putch = writer_putc, .f_putstr = writer_puts},
    .in_transmit = 0,
    .lost_char_count = 0,
    .tx_cnt = 0,
    .error_count = 0,
    .fifo = {.fifoState = {.size = sizeof(usb_hid_o_data), .start = 0, .end = 0, .count = 0, .errors = 0},
             .array = usb_hid_o_data,
             .initDone = true},
    .f_transmit = usb_hid_writer_transmit,
    .enable = true,
    .busy = false,
};

bool usb_hid_writer_init(void) {
    bool res = true;
    memset(usb_hid_o_data, 0, sizeof(usb_hid_o_data));
    return res;
}
