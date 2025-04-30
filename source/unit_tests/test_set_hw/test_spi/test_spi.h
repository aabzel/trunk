#ifndef TEST_SPI_H
#define TEST_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"


#ifdef HAS_SPI_WAIT_WRITE
bool test_spi_wait_write(void) ;
#define TEST_SUIT_SPI_WAIT_WRITE              \
    {"spi_wait_write", test_spi_wait_write},

#else
#define TEST_SUIT_SPI_WAIT_WRITE
#endif

#ifndef HAS_HW_TESTS
#error "It is needed HAS_HW_TESTS option for that component"
#endif

#ifdef HAS_SPI0
bool test_spi0_read(void) ;
bool test_spi0_write(void) ;
#define TEST_SUIT_SPI0 {"spi0_write", test_spi0_write} , {"spi0_read", test_spi0_read},
#else
#define TEST_SUIT_SPI0
#endif

#ifdef HAS_SPI1
bool test_spi1_read(void) ;
bool test_spi1_write(void) ;
#define TEST_SUIT_SPI1 {"spi1_write", test_spi1_write} , {"spi1_read", test_spi1_read},
#else
#define TEST_SUIT_SPI1
#endif

#ifdef HAS_SPI2
bool test_spi2_read(void) ;
bool test_spi2_write(void) ;
#define TEST_SUIT_SPI2 {"spi2_write", test_spi2_write},  {"spi2_read", test_spi2_read},
#else
#define TEST_SUIT_SPI2
#endif

#ifdef HAS_SPI3
bool test_spi3_read(void) ;
bool test_spi3_write(void) ;
#define TEST_SUIT_SPI3 {"spi3_write", test_spi3_write},  {"spi3_read", test_spi3_read},
#else
#define TEST_SUIT_SPI3
#endif

#ifdef HAS_SPI4
bool test_spi4_read(void) ;
bool test_spi4_write(void) ;
#define TEST_SUIT_SPI4 {"spi4_write", test_spi4_write},  {"spi4_read", test_spi4_read},
#else
#define TEST_SUIT_SPI4
#endif

#define TEST_SUIT_SPI_GENERAL          \
    TEST_SUIT_SPI0                     \
    TEST_SUIT_SPI1                     \
    TEST_SUIT_SPI2                     \
    TEST_SUIT_SPI3                     \
    TEST_SUIT_SPI4


#define TEST_SUIT_SPI          \
    TEST_SUIT_SPI_GENERAL      \
    TEST_SUIT_SPI_WAIT_WRITE

#ifdef __cplusplus
}
#endif

#endif /* TEST_SPI_H */
