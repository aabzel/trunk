#ifndef TCAN4550_DRV_H
#define TCAN4550_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "tcan4550_constants.h"
#include "tcan4550_reg.h"
#include "tcan4550_types.h"

#define TCAN4550_PERIOD_US 1
#define CAN_BAUD_RATE_DFLT 250000U /*Bit/s*/
#define CAN_XTAL_HZ 40000000U
#define MRAM_SZ 2048U /*Byte*/

//#define DEVICE_ID "TCAN4550"
#define OP_CODE_READ 0x41
#define OP_CODE_WRITE 0x61

typedef struct {
    uint32_t bit_rate;
    bool lock;
    bool connected;
    bool wdt;
    CanDevMode_t mode;
    LastErrorCode_t lec;
    volatile uint32_t int_cnt;
} Can4550State_t;

typedef struct {
    uint32_t tx_frame_cnt;
    uint32_t rx_frame_cnt;
    Can4550State_t set;
    Can4550State_t cur;
} Can4550_t;

typedef struct xHeaderCom_t {
    uint8_t op_code;
    uint16_t addr;
    uint8_t words_cnt;
} __attribute__((packed)) HeaderCom_t;

typedef struct xTcan4550Reg_t {
    uint16_t addr;
    char* name;
} Tcan4550Reg_t;

extern const uint64_t exp_dev_id;

extern Can4550_t CanPhy;
extern const Tcan4550Reg_t tCan4550RegLUT[];

uint8_t dlc_2_bytes(uint8_t dlc_code);
uint8_t bytes_2_dlc(uint8_t len);

bool is_tcan4550_connected(void);
bool is_tcan4550_protected_reg_locked(tCanRegCCctrl_t* reg);
bool is_tcan4550_protected_reg_unlock(tCanRegCCctrl_t* reg);
bool tcan4550_init(void);
bool tcan4550_deinit(void);
bool tcan4550_set_mode(CanDevMode_t dev_mode);
bool tcan4550_set_lock(bool state);
bool tcan4550_set_bit_rate(uint32_t des_bit_rate);
bool tcan4550_proc(void);
bool tcan4550_reset(void);
bool tcan4550_send_std(uint32_t id, uint64_t data, uint8_t len);
bool tcan4550_send_ext(uint32_t id, uint64_t data, uint8_t len);
bool tcan4550_send_spi_burst(uint32_t word);
bool tcan4550_clear_mram(void);
bool tcan4550_chip_select(bool state);
bool tcan4550_read(uint16_t address, uint8_t len, uint8_t* out_array, uint32_t size);
bool tcan4550_read_reg(uint16_t address, uint32_t* out_reg);
bool tcan4550_write_reg(uint16_t address, uint32_t reg_val);
bool tcan4550_write_verify_reg(uint16_t address, uint32_t reg_val);
bool tcan4550_configure_interrupt(tCanRegIntEn_t* int_en);
bool tcan4550_write_sid_filter(uint8_t filter_index, tCan4550SidFilter_t* filter);
bool tcan4550_send_spi_header(uint8_t opcode, uint16_t address, uint8_t words);
bool tcan4550_write_reg(uint16_t address, uint32_t reg_val);
bool tcan4550_write_reg_lazy(uint16_t address, uint32_t reg_val);
bool tcan4550_int_isr(void);
uint32_t tcan4550_get_bit_rate(void);
const char* tcan4550_get_reg_name(uint16_t addr);
uint16_t tcan4550_get_reg_cnt(void);
uint32_t tcan4550_read_spi_burst(void);
CanDevMode_t tcan4550_get_mode(void);
uint8_t tcan4550_get_fifo_cnt(uint8_t fifo_num);

#ifdef __cplusplus
}
#endif

#endif /* TCAN4550_DRV_H  */
