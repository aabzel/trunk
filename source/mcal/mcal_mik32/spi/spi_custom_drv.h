#ifndef SPI_CUSTOM_DRV_H
#define SPI_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

uint8_t spi_base_2_num(SPI_TypeDef* Instance);

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_DRV_H  */
