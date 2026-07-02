#ifndef TEST_SPI_INTERRUPT_H
#define TEST_SPI_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "test_hw_dep_check.h"
#include "std_includes.h"


bool test_spi_read_interrupt(uint8_t num);
bool test_spi_write_interrupt(uint8_t num);
bool test_spi_write_read_interrupt(uint8_t num);


#ifdef HAS_SPI1

bool test_spi1_write_interrupt(void);
bool test_spi1_read_interrupt(void);
bool test_spi1_write_read_interrupt(void);

#define TEST_SUIT_SPI1_INTERRUPT                                                 \
           {"spi1_write_interrupt", test_spi1_write_interrupt},                  \
           {"spi1_read_interrupt", test_spi1_read_interrupt},                    \
           {"spi1_write_read_interrupt", test_spi1_write_read_interrupt},

#else
#define TEST_SUIT_SPI1_INTERRUPT
#endif

#ifdef HAS_SPI2

bool test_spi2_write_interrupt(void);
bool test_spi2_read_interrupt(void);
bool test_spi2_write_read_interrupt(void);

#define TEST_SUIT_SPI2_INTERRUPT                                                 \
           {"spi2_write_interrupt", test_spi2_write_interrupt},                  \
           {"spi2_read_interrupt", test_spi2_read_interrupt},                    \
           {"spi2_write_read_interrupt", test_spi2_write_read_interrupt},

#else
#define TEST_SUIT_SPI2_INTERRUPT
#endif


#ifdef HAS_SPI3

bool test_spi3_write_interrupt(void);
bool test_spi3_read_interrupt(void);
bool test_spi3_write_read_interrupt(void);

#define TEST_SUIT_SPI3_INTERRUPT                                                 \
           {"spi3_write_interrupt", test_spi3_write_interrupt},                  \
           {"spi3_read_interrupt", test_spi3_read_interrupt},                    \
           {"spi3_write_read_interrupt", test_spi3_write_read_interrupt},


#else
#define TEST_SUIT_SPI3_INTERRUPT
#endif


#define TEST_SUIT_SPI_INTERRUPT      \
        TEST_SUIT_SPI1_INTERRUPT     \
        TEST_SUIT_SPI2_INTERRUPT     \
        TEST_SUIT_SPI3_INTERRUPT



#ifdef __cplusplus
}
#endif

#endif /* TEST_SPI_INTERRUPT_H */
