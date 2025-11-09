#ifndef LIS3DH_CONST_H
#define LIS3DH_CONST_H

#include "time_mcal.h"
#include "lis3dh_dep.h"


#define LIS3DH_I2C_ADDR_1 0x19
#define LIS3DH_I2C_ADDR_0 0x18
#define LIS3DH_REG_CNT 42
#define REG_SET_TRY_CNT 1
#define LIS3DH_ID_VALUE 0x33
#define LIS3DH_POLL_PERIOD_US MSEC_2_USEC(200)
#define LIS3DH_LINK_POLL_PERIOD_US SEC_2_USEC(5)

//7 Register mapping
typedef enum {
    LIS3DH_REG_STATUS_REG_AUX=0x07,
    LIS3DH_REG_OUT_ADC1_L=0x08,
    LIS3DH_REG_OUT_ADC1_H=0x09,
    LIS3DH_REG_OUT_ADC2_L=0x0A,
    LIS3DH_REG_OUT_ADC2_H=0x0B,
    LIS3DH_REG_OUT_ADC3_L=0x0C,
    LIS3DH_REG_OUT_ADC3_H=0x0D,
    LIS3DH_REG_WHO_AM_I=0x0F,
    LIS3DH_REG_TEMP_CFG_REG=0x1F,
    LIS3DH_REG_STATUS_REG=0x27,
    LIS3DH_REG_OUT_X_L=0x28,
    LIS3DH_REG_OUT_X_H=0x29,
    LIS3DH_REG_OUT_Y_L=0x2A,
    LIS3DH_REG_OUT_Y_H=0x2B,
    LIS3DH_REG_OUT_Z_L=0x2C,
    LIS3DH_REG_OUT_Z_H=0x2D,
    LIS3DH_REG_FIFO_SRC_REG=0x2F,
    LIS3DH_REG_INT1_SRC=0x31,
    LIS3DH_REG_INT2_SRC=0x35,
    LIS3DH_REG_CLICK_SRC=0x39,
    LIS3DH_REG_CTRL_REG0=0x1E,
    LIS3DH_REG_CTRL_REG1=0x20,
    LIS3DH_REG_CTRL_REG2=0x21,
    LIS3DH_REG_CTRL_REG3=0x22,
    LIS3DH_REG_CTRL_REG4=0x23,
    LIS3DH_REG_CTRL_REG5=0x24,
    LIS3DH_REG_CTRL_REG6=0x25,
    LIS3DH_REG_REFERENCE=0x26,
    LIS3DH_REG_FIFO_CTRL_REG=0x2E,
    LIS3DH_REG_INT1_CFG=0x30,
    LIS3DH_REG_INT1_THS=0x32,
    LIS3DH_REG_INT1_DURATION=0x33,
    LIS3DH_REG_INT2_CFG=0x34,
    LIS3DH_REG_INT2_THS=0x36,
    LIS3DH_REG_INT2_DURATION=0x37,
    LIS3DH_REG_CLICK_CFG=0x38,
    LIS3DH_REG_CLICK_THS=0x3A,
    LIS3DH_REG_TIME_LIMIT=0x3B,
    LIS3DH_REG_TIME_LATENCY=0x3C,
    LIS3DH_REG_TIME_WINDOW=0x3D,
    LIS3DH_REG_ACT_THS=0x3E,
    LIS3DH_REG_ACT_DUR=0x3F,
    LIS3DH_REG_UNDEF = 0xFF,
} Lis3dhRegAddr_t;


// Table 31. Data rate configuration (ODR)
//ODR - xxxx Data rate
typedef enum {
    LIS3DH_DATA_RATE_POWER_DOWN = 0,  //Power-down mode
    LIS3DH_DATA_RATE_1_HZ = 1,        //HR / Normal / Low-power mode (1 Hz)
    LIS3DH_DATA_RATE_10_HZ = 2,       //HR / Normal / Low-power mode (10 Hz)
    LIS3DH_DATA_RATE_25_HZ = 3,       //HR / Normal / Low-power mode (25 Hz)
    LIS3DH_DATA_RATE_50_HZ = 4,       //HR / Normal / Low-power mode (50 Hz)
    LIS3DH_DATA_RATE_100_HZ = 5,      //HR / Normal / Low-power mode (100 Hz)
    LIS3DH_DATA_RATE_200_HZ = 6,      //HR / Normal / Low-power mode (200 Hz)
    LIS3DH_DATA_RATE_400_HZ = 7,      //HR / Normal / Low-power mode (400 Hz)
    LIS3DH_DATA_RATE_1600_HZ = 8,     //Low power mode (1.60 kHz)
    LIS3DH_DATA_RATE_1344_HZ = 9,     //HR / normal (1.344 kHz); Low-power mode (5.376 kHz)
    LIS3DH_DATA_RATE_5376_HZ = 10,    //HR / normal (1.344 kHz); Low-power mode (5.376 kHz)
} Lis3dhDataRate_t;


// see Table 34. High-pass filter mode configuration
typedef enum {
    LIS3DH_HIGH_PASS_FILT_NORMAL_REFERENCE  = 0,  // Normal mode (reset by reading REFERENCE (26h))
    LIS3DH_HIGH_PASS_FILT_REFERENCE  = 1,  // Reference signal for filtering
    LIS3DH_HIGH_PASS_FILT_NORMAL  = 2,  // Normal mode
    LIS3DH_HIGH_PASS_FILT_AUTORESET  = 3,  // Autoreset on interrupt event
    LIS3DH_HIGH_PASS_FILT_UNDEF  = 4,  //
} Lis3dhHighPassFilterMode_t;


// see Table 39. Self-test mode configuration
typedef enum {
    LIS3DH_SELF_TEST_NORMAL = 0, //Normal mode
    LIS3DH_SELF_TEST_0 = 1, //Self-test 0
    LIS3DH_SELF_TEST_1 = 2, //Self-test 1
    LIS3DH_SELF_TEST_RESERV = 3, // reserved
    LIS3DH_SELF_TEST_UNDEF = 4, //
} Lis3dhSelfTest_t;


// see Full-scale selection.
typedef enum {
    LIS3DH_FULL_SCALE_2G   =0 , // 00: ±2 g
    LIS3DH_FULL_SCALE_4G   =1 , //  01: ±4
    LIS3DH_FULL_SCALE_8G   =2 , // 10: ±8 g
    LIS3DH_FULL_SCALE_16G  =3 , // 11: ±16 g
    LIS3DH_FULL_SCALE_UNDEF   =4 , //
} Lis3dhFullScale_t;

typedef enum {
    LIS3DH_BIT_DEPTH_8=8,
    LIS3DH_BIT_DEPTH_10=10,
    LIS3DH_BIT_DEPTH_12=12,
    LIS3DH_BIT_DEPTH_UNDEF=0
}Lis3dhBitDepth_t;

//Table 10. Operating mode selection
typedef enum {
    LIS3DH_OPERATION_MODE_NORMAL = 0, //Normal mode
    LIS3DH_OPERATION_MODE_HIGH_RESOLUTION = 1, //High-resolution mode
    LIS3DH_OPERATION_MODE_LOW_POWER = 2, //Low-power mode
    LIS3DH_OPERATION_MODE_ERROR = 3, //Not allowed
    LIS3DH_OPERATION_MODE_UNDEF = 4 //
} Lis3dhOperationMode_t;

//Table 50. FIFO mode configuration
typedef enum {
    LIS3DH_FIFO_MODE_BYPASS=0,
    LIS3DH_FIFO_MODE_FIFO=1,
    LIS3DH_FIFO_MODE_STREAM=2,
    LIS3DH_FIFO_MODE_STREAM_TO_FIFO=3,
    LIS3DH_FIFO_MODE_UNDEF=4
}Lis3dhFifoMode_t;

typedef enum {
    LIS3DH_IF_I2C   = 1 ,
    LIS3DH_IF_SPI   = 2 ,
    LIS3DH_IF_UNDEF = 0 ,
} Lis3dhInterface_t;


// SPI serial interface mode selection.
typedef enum {
    LIS3DH_SERIAL_IF_MODE_SPI = 0 ,   // 0: 4-wire interface
    LIS3DH_SERIAL_IF_MODE_3_WIRE = 1 ,// 1: 3-wire interface
    LIS3DH_SERIAL_IF_MODE_UNDEF = 2 ,
} Lis3dhSerialInterfaceMode_t;



typedef enum {
    LIS3DH_MS_ADDR_STATIC = 0 ,  // When 0, the address remains unchanged in multiple read/write commands
    LIS3DH_MS_ADDR_AUTO_INC = 1 , // When 1, the address is auto incremented in multiple read/write commands
    LIS3DH_MS_UNDEF = 2 ,
} Lis3dhMoveMultiple_t;

typedef enum {
    LIS3DH_SPI_WRITE = 0 , // When 0, the data DI(7:0) is written into the device
    LIS3DH_SPI_READ  = 1 , // When 1, the data DO(7:0) from the device is read
    LIS3DH_SPI_UNDEF = 2 ,
} Lis3dhSpiDirrection_t;


#endif /* LIS3DH_CONST_H */
