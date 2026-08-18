
#include "deca_device_api.h"

#include "decadriver_config.h"
#include "gpio_diag.h"
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "spi_drv.h"
//#include "timer_utils.h"
#include "time_mcal.h"

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn writetospi()
 *
 * @brief
 * NB: In porting this to a particular microprocessor, the implementer needs to define the two low
 * level abstract functions to write to and read from the SPI the definitions should be in deca_spi.c file.
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 *
 * Note: The body of this function is defined in deca_spi.c and is platform specific
 *
 * input parameters:
 * @param headerLength  - number of bytes header being written
 * @param headerBuffer  - pointer to buffer containing the 'headerLength' bytes of header to be written
 * @param bodylength    - number of bytes data being written
 * @param bodyBuffer    - pointer to buffer containing the 'bodylength' bytes od data to be written
 *
 * output parameters
 *
 * returns DWT_SUCCESS for success, or DWT_ERROR for error
 */
int writetospi(uint16 headerLength, const uint8* headerBuffer, uint32 bodylength, const uint8* bodyBuffer) {
    int ret = DWT_ERROR;
    bool res = false;
    LOG_PARN(DECA, "SPIWrite %u byte, ChipSel: %s", headerLength, GpioPadToStr(DecaDriverConfig.chip_select));
    res = gpio_set_logic_level(DecaDriverConfig.chip_select.byte, GPIO_LVL_LOW);
    // time_delay_us(10);

#ifdef HAS_CHIP_SELECT_VERIFY
    GpioLogicLevel_t logic_level_eff = GPIO_LVL_UNDEF;
    res = gpio_get_state(DecaDriverConfig.chip_select.byte, &logic_level_eff);
    if(GPIO_LVL_LOW == logic_level_eff) {
#endif
        res = spi_api_write(DecaDriverConfig.spi_num, headerBuffer, headerLength);
        if(res) {
            res = spi_api_write(DecaDriverConfig.spi_num, bodyBuffer, bodylength);
            if(res) {
                ret = DWT_SUCCESS;
            }
        }
#ifdef HAS_CHIP_SELECT_VERIFY
    } else {
        LOG_ERROR(DECA, "ChipSelSetErr");
    }
#endif
    res = gpio_set_logic_level(DecaDriverConfig.chip_select.byte, GPIO_LVL_HI);
    return ret;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn readfromspi()
 *
 * @brief
 * NB: In porting this to a particular microprocessor, the implementer needs to define the two low
 * level abstract functions to write to and read from the SPI the definitions should be in deca_spi.c file.
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 *
 * Note: The body of this function is defined in deca_spi.c and is platform specific
 *
 * input parameters:
 * @param headerLength  - number of bytes header to write
 * @param headerBuffer  - pointer to buffer containing the 'headerLength' bytes of header to write
 * @param readlength    - number of bytes data being read
 * @param readBuffer    - pointer to buffer containing to return the data (NB: size required = headerLength +
 * readlength)
 *
 * output parameters
 *
 * returns DWT_SUCCESS for success (and the position in the buffer at which data begins), or DWT_ERROR for error
 */
int readfromspi(uint16 headerLength, const uint8* headerBuffer, uint32 readlength, uint8* readBuffer) {
    int ret = DWT_ERROR;
    bool res = false;
    LOG_PARN(DECA, "SPI%u Read %u byte, ChipSel: %s", DecaDriverConfig.spi_num, readlength,
             GpioPadToStr(DecaDriverConfig.chip_select));
    res = gpio_set_logic_level(DecaDriverConfig.chip_select.byte, (GpioLogicLevel_t)GPIO_LVL_LOW);
    // time_delay_us(10);
#ifdef HAS_CHIP_SELECT_VERIFY
    GpioLogicLevel_t logic_level_eff = GPIO_LVL_UNDEF;
    res = gpio_get_state(DecaDriverConfig.chip_select.byte, &logic_level_eff);
    if(GPIO_LVL_LOW == logic_level_eff) {
#endif
        res = spi_api_write(DecaDriverConfig.spi_num, headerBuffer, headerLength);
        if(res) {
            LOG_PARN(DECA, "WriteHeaderOk %u byte", headerLength);
            res = spi_api_read(DecaDriverConfig.spi_num, readBuffer, readlength);
            if(res) {
                ret = DWT_SUCCESS;
                LOG_PARN(DECA, "SPIReadOk %u byte", readlength);
            } else {
                LOG_ERROR(DECA, "SPI%u ReadErr %u byte", DecaDriverConfig.spi_num, readlength);
            }
        } else {
            LOG_ERROR(DECA, "SPI%u WriteErr %u byte", DecaDriverConfig.spi_num, headerLength);
        }
#ifdef HAS_CHIP_SELECT_VERIFY
    } else {
        LOG_ERROR(DECA, "ChipSelSetErr");
    }
#endif
    res = gpio_set_logic_level(DecaDriverConfig.chip_select.byte, GPIO_LVL_HI);
    return ret;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn deca_sleep()
 *
 * @brief Wait for a given amount of time.
 * NB: The body of this function is defined in deca_sleep.c and is platform specific
 *
 * input parameters:
 * @param time_ms - time to wait in milliseconds
 *
 * output parameters
 *
 * no return value
 */
void deca_sleep(unsigned int time_ms) { time_delay_ms((int32_t)time_ms); }

decaIrqStatus_t decamutexon(void) {
    decaIrqStatus_t ret = 0;
    return ret;
}

void decamutexoff(decaIrqStatus_t s) {}
