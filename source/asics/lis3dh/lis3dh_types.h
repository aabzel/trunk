#ifndef LIS3DH_TYPES_H
#define LIS3DH_TYPES_H

#include "std_includes.h"
#include "storage_const.h"
#include "lis3dh_registers_types.h"
#include "lis3dh_const.h"
#include "data_types.h"
#include "vector_types.h"


/*  */
typedef union {
    uint8_t byte;
    struct {
        uint8_t register_address : 6;   /* bit 5-0   address AD(5:0). This is the address field of
                                                     the indexed register */
        uint8_t ms : 1;   /* bit 6  When 0, the address remains unchanged in multiple read/write commands
                                    When 1, the address is auto incremented in multiple read/write commands */
        uint8_t rw : 1;  /* bit 7   When 0, the data DI(7:0) is written into the device
                                    When 1, the data DO(7:0) from the device is read.*/
    };
}Lis3dhSpiHeader_t;



typedef union {
    uint8_t buff[6];
    struct{
        U16_bit_t X;
        U16_bit_t Y;
        U16_bit_t Z;
    }__attribute__((__packed__));
}__attribute__((__packed__))Lis3dhAccelRegs_t;

//The value is expressed as two’s complement left-justified.
typedef struct {
    U16_bit_t X;
    U16_bit_t Y;
    U16_bit_t Z;
    VectorF_t AccelReal;
//    float X_real;
//    float Y_real;
//    float Z_real;
}Lis3dhAcceleration_t;

typedef struct {
    Lis3dhRegAddr_t addr;
    Lis3dhRegUniversal_t Reg; /*register value*/
}Lis3dhRegVal_t;

#ifdef HAS_SPI
#define LIS3DH_SPI_COMMON_VARIABLE      \
    uint8_t spi_num;                    \
    Pad_t ChipSelect;
#else
#define LIS3DH_SPI_COMMON_VARIABLE
#endif

#ifdef HAS_I2C
#define LIS3DH_I2C_COMMON_VARIABLE      \
    uint8_t chip_addr;                  \
    uint8_t i2c_num;                    \
    uint8_t sa0_pin_value;
#else
#define LIS3DH_I2C_COMMON_VARIABLE
#endif

#define LIS3DH_COMMON_VARIABLE      \
    LIS3DH_I2C_COMMON_VARIABLE      \
    LIS3DH_SPI_COMMON_VARIABLE      \
    Lis3dhBitDepth_t bit_depth;     \
    Lis3dhInterface_t interface;    \
    uint8_t num;                    \
    bool valid;

typedef struct {
    LIS3DH_COMMON_VARIABLE
    Lis3dhRegVal_t* RegConfig;
    uint32_t cfg_reg_cnt;
    char *name;
}Lis3dhConfig_t;

typedef struct{
    LIS3DH_COMMON_VARIABLE
   // Lis3dhRegVal_t Register[LIS3DH_REG_CNT];
    bool init;
    bool log_on;
    bool unproc_sample;
    bool link_ok;
    bool log_inplace_on;
    int8_t sensitivity;
    FloatValue_t abs_accel;
    Lis3dhOperationMode_t operation_mode;
    Lis3dhAcceleration_t Acceleration;
}Lis3dhHandle_t;

//Table 10. Operating mode selection
typedef struct {
    int8_t sensitivity; //mg/digit
    char* name;
    int8_t bit_depth;//bit data output)
    uint8_t low_power_enable;//LPen Low-power mode enable
    uint8_t high_resolution_enable;//High-resolution output mode
    Lis3dhOperationMode_t operation_mode;//
    Lis3dhFullScale_t full_scale;
}Lis3dhOperationModeInfo_t;


#endif /* LIS3DH_TYPES_H */
