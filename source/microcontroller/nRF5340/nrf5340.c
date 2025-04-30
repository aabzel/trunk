#include "nrf5340.h"

#include "data_types.h"
#include "log.h"
#include "nrf_ficr.h"

Port_t PortLetter2PortNum(char port) {
    Port_t port_num = PORT_UNDEF;
    switch(port) {
    case '0':
        port_num = 0;
        break;
    case '1':
        port_num = 1;
        break;
    }
    return port_num;
}

bool gpio_is_valid_pad(uint8_t pad_num) {
    bool res = false;
    Pad_t Pad;
    Pad.byte = pad_num;
    if(Pad.port <= GPIO_PORT_MAX) {
        if(Pad.pin <= GPIO_PIN_MAX) {
            res = true;
        }
    }
    return res;
}

/*
 * see page 122 5.4.2.1.2 INFO.DEVICEID[n] (n=0..1)
 * Table 38: Instances
 * Register         Offset       Description
 * INFO.DEVICEID[n] 0x204        Device identifier
 * DEVICEID[0] contains the least significant bits of the device identifier.
 * DEVICEID[1] contains the most significant bits of the device identifier.
 */

bool nrf5340_get_id(uint64_t* const dev_id) {
    bool res = false;
    if(dev_id) {
        U64_bit_t un64;
        un64.u32[0] = nrf_ficr_deviceid_get(NRF_FICR, 0);
        un64.u32[1] = nrf_ficr_deviceid_get(NRF_FICR, 1);
        if(un64.u64) {
            if(un64.u64 < UINT64_MAX) {
                *dev_id = un64.u64;
                res = true;
            }
        }
    }
    return res;
}

bool mcu_init(void) {
    bool res = false;
    LOG_WARNING(SYS, "MCU init");
    uint64_t dev_id = 0;
    /* N/A 0x01FF0000 FICR FICR NS NA Factory information configuration */
    LOG_INFO(MCU, "FICR: %p", NRF_FICR);

    res = nrf5340_get_id(&dev_id);
    LOG_INFO(MCU, "McuID: 0x%llx=%llu", dev_id, dev_id);

    uint32_t codesize = nrf_ficr_codesize_get(NRF_FICR);
    LOG_INFO(MCU, "CodeSize: %u Pages", codesize);

    uint32_t codepagesize = nrf_ficr_codepagesize_get(NRF_FICR);
    LOG_INFO(MCU, "CodePageSize: %u Bytes", codepagesize);

    LOG_INFO(MCU, "CodeSize: %u Bytes", codepagesize * codesize);
    return res;
}
