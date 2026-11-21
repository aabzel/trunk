#ifndef ILI9341_TYPES_H
#define ILI9341_TYPES_H

#include "std_includes.h"
#include "ili9341_const.h"
#include "gpio_types.h"
#include "fonts_english.h"

/* 8.2.29. Memory Access Control (36h) */
typedef union {
    uint8_t byte;
    struct {
        uint8_t res: 2; // D0:
        uint8_t MH        : 1; // D2: Horizontal Refresh Order
        uint8_t BGR       : 1; // D3: RGB-BGR Order (0=RGB, 1=BGR)
        uint8_t ML        : 1; // D4: Vertical Refresh Order
        uint8_t MV        : 1; // D5: Row / Column Exchange
        uint8_t MX        : 1; // D6: Column Address Order
        uint8_t MY        : 1; // D7: Row Address Order
    } ;
} Ili9341ParamMemoryAccessControl_t;


typedef struct  {
    uint16_t x;
    uint16_t y;
} DotU16_t;

typedef struct {
    uint32_t num;
    bool valid;
    Ili9341Cmd_t command;
    uint8_t *data;
    uint32_t size;
} Ili9341InitConfig_t;

/*65K color: 16-bit/pixel (RGB 5-6-5 bits input)*/
typedef union {
    uint16_t word;
    struct {
        uint16_t blue:5;
        uint16_t green:6;
        uint16_t red:5;
    }__attribute__((__packed__)) ;
} __attribute__((__packed__))  Ili9341Pixel_t;



/*see 8.2.3. Read display identification information (04h)*/
typedef union {
    uint8_t buff[4];
    uint32_t dword;
    struct {
        uint8_t dummy;        // 1st Parameter: Dummy Read
        uint8_t man_info;     // 2nd Parameter: Send LCD module's manufacturer information
        uint8_t panel_type;   // 3rd Parameter: Send panel type and LCM/driver version information
        uint8_t drv_info;     // 4th Parameter: Send module/driver information
    };
} Ili9341Id_t;


typedef union {
    uint8_t buff[4];
    uint32_t dword;
    struct {
        uint8_t sc15_8;        //
        uint8_t sc7_0;     //
        uint8_t ec15_8;   //
        uint8_t ec7_0;     //
    };
} Ili9341ColumnAddressSetParam_t;


//8.2.21. Page Address Set (2Bh)
typedef union {
    uint8_t buff[4];
    uint32_t dword;
    struct {
        uint8_t sp15_8;    //
        uint8_t sp7_0;     //
        uint8_t ep15_8;    //
        uint8_t ep7_0;     //
    };
} Ili9341PageAddressSetParam_t;





/*8.2.46. Read ID1 (DAh)*/
typedef union {
    uint8_t buff[2];
    uint16_t word;
    struct {
        uint8_t dummy;                // 1st Parameter: Dummy Read
        uint8_t manufacturer_id ;     // The 2nd parameter is LCD module’s manufacturer ID.
    };
} Ili9341ManId1_t;

/*8.2.47. Read ID2 (DBh) */
typedef union {
    uint8_t buff[2];
    uint16_t word;
    struct {
        uint8_t dummy;          // The 1st parameter is dummy data.
        uint8_t driver_version; // The 2nd parameter is LCD module/driver version ID and the ID parameter range is from 80h to FFh.
    };
} Ili9341ManId2_t;


#define ILI9341_COMMON_VARIABLES                       \
    uint8_t spi_num;                                   \
    ScreenOrientation_t screen_orientation;            \
    char* name;                                        \
    uint8_t num;                                       \
    uint32_t update_period_ms;                         \
    Pad_t LedPad;                                      \
    Pad_t chip_select;                                 \
    Pad_t ResetPad;                                    \
    Pad_t DcxPad;                                      \
    bool valid;


typedef struct {
    ILI9341_COMMON_VARIABLES
}Ili9341Config_t;




typedef struct {
    ILI9341_COMMON_VARIABLES
    bool init;
#ifdef HAS_ILI9341_FRAME_BUFFER
    volatile uint16_t frameBuffer[ILI9341_FRAME_BUFFER_SIZE_W];
#endif
    uint32_t spin;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;

    FontDef cur_font;
    uint16_t text_color;
    uint16_t bgcolor;
}Ili9341Handle_t;


#endif /* ILI9341_TYPES_H */
