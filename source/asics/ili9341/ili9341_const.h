#ifndef ILI9341_CONST_H
#define ILI9341_CONST_H

#include "time_mcal.h"
#include "ili9341_dep.h"

#define ILI9341_VERSION 3
#define ILI9341_NARROW 240
#define ILI9341_WIDE 320
#define ILI9341_FRAME_BUFFER_SIZE_W (ILI9341_WIDTH*ILI9341_HEIGHT)
#define ILI9341_PERIOD_US MSEC_2_USEC(500)


typedef enum {
    SCREEN_ORIENTATION_UNDEF = 0,
    SCREEN_ORIENTATION_VERTICAL = 1,
    SCREEN_ORIENTATION_HORIZONTAL = 2
}ScreenOrientation_t;


typedef enum {
    ILI9341_DXC_CTRL_DATA = 1,
    ILI9341_DXC_CTRL_COMMAND = 2,
    ILI9341_DXC_CTRL_UNDEF = 3
}Ili9341DcCtrl_t;


/**
 * Команды драйвера ILI9341 (согласно таблице 8.1 Command List)
 */
typedef enum {
    /* --- Основные команды (Level 1) --- */
    ILI9341_CMD_NOP        = 0x00,  // No Operation (пустая команда)
    ILI9341_CMD_SWRESET    = 0x01,  // Software Reset
    ILI9341_CMD_RDDID      = 0x04,  // Read Display Identification Information
    ILI9341_CMD_RDDST      = 0x09,  // Read Display Status

    /* --- Команды чтения состояния (Read) --- */
    ILI9341_CMD_RDMODE     = 0x0A,  // Read Display Power Mode
    ILI9341_CMD_RDMADCTL   = 0x0B,  // Read Display MADCTL
    ILI9341_CMD_RDPIXFMT   = 0x0C,  // Read Display Pixel Format
    ILI9341_CMD_RDIMGFMT   = 0x0D,  // Read Display Image Format
    ILI9341_CMD_RDSELFDIAG = 0x0F,  // Read Display Self-Diagnostic Result

    /* --- Управление режимами питания и отображения --- */
    ILI9341_CMD_SLPIN      = 0x10,  // Enter Sleep Mode
    ILI9341_CMD_SLEEP_OUT     = 0x11,  // Sleep Out
    ILI9341_CMD_PTLON      = 0x12,  // Partial Mode ON
    ILI9341_CMD_NORMAL_MODE_ON      = 0x13,  // Normal Display Mode ON

    ILI9341_CMD_POWER_ON   = 0xED,  //8.4.6 Power on sequence control (EDh)

    /* --- Инверсия и гамма --- */
    ILI9341_CMD_INVOFF     = 0x20,  // Display Inversion OFF
    ILI9341_CMD_INVON      = 0x21,  // Display Inversion ON
    ILI9341_CMD_GAMMASET   = 0x26,  // Gamma Set

    /* --- Основное управление дисплеем --- */
    ILI9341_CMD_DISPOFF    = 0x28,  // Display OFF
    ILI9341_CMD_DISPLAY_ON = 0x29,  // Display ON
    ILI9341_CMD_COLUMN_ADDRESS_SET      = 0x2A,  // Column Address Set
    ILI9341_CMD_PAGE_ADDRESS_SET      = 0x2B,  // Page Address Set
    ILI9341_CMD_MEMORY_WRITE = 0x2C,  // 8.2.22. Memory Write (2Ch)
    ILI9341_CMD_MEMORY_READ  = 0x2E,  // 8.2.24. Memory Read (2Eh)

    ILI9341_CMD_PUMP_RATIO_CONTROL  = 0xF7,//8.4.8 Pump ratio control (F7h)
    ILI9341_CMD_DRIVER_TIMING_CONTROL_A = 0xE8,// 8.4.3 Driver timing control A (E8h)
    ILI9341_CMD_POWER_CONTROL_A = 0xCB, //8.4.1 Power control A (CBh)

    /* --- Частичный режим и скроллинг --- */
    ILI9341_CMD_PTLAR      = 0x30,  // Partial Area
    ILI9341_CMD_VSCRDEF    = 0x33,  // Vertical Scrolling Definition
    ILI9341_CMD_MADCTL     = 0x36,  // Memory Access Control
    ILI9341_CMD_VSCRSADD   = 0x37,  // Vertical Scrolling Start Address

    ILI9341_CMD_DRIVER_TIMING_CONTROL_B = 0xEA, //8.4.5 Driver timing control B (EAh)

    /* --- Формат пикселей --- */
    ILI9341_CMD_PIXFMT     = 0x3A,  // COLMOD: Pixel Format Set

    /* --- Управление кадрами (Frame Rate) --- */
    ILI9341_CMD_FRMCTR1    = 0xB1,  // Frame Rate Control (Normal Mode)
    ILI9341_CMD_FRMCTR2    = 0xB2,  // Frame Rate Control (Idle Mode)
    ILI9341_CMD_FRMCTR3    = 0xB3,  // Frame Rate Control (Partial Mode)
    ILI9341_CMD_INVCTR     = 0xB4,  // Display Inversion Control
    ILI9341_CMD_DFUNCTR    = 0xB6,  // Display Function Control

    ILI9341_CMD_ENABLE_3G  = 0xF2,  //8.4.7 Enable 3G (F2h)

    /* --- Управление питанием --- */
    ILI9341_CMD_PWCTR1     = 0xC0,  // Power Control 1
    ILI9341_CMD_PWCTR2     = 0xC1,  // 8.3.17. Power Control 2 (C1h)
    ILI9341_CMD_PWCTR3     = 0xC2,  // Power Control 3
    ILI9341_CMD_PWCTR4     = 0xC3,  // Power Control 4
    ILI9341_CMD_PWCTR5     = 0xC4,  // Power Control 5
    ILI9341_CMD_PWCTR_B    = 0xCF,  // 8.4.2 Power control B (CFh)
    ILI9341_CMD_VMCTR1     = 0xC5,  // VCOM Control 1
    ILI9341_CMD_VMCTR2     = 0xC7,  // VCOM Control 2

    /* --- Чтение ID (альтернативные регистры) --- */
    ILI9341_CMD_RDID1      = 0xDA,  // Read ID1
    ILI9341_CMD_RDID2      = 0xDB,  // Read ID2
    ILI9341_CMD_RDID3      = 0xDC,  // Read ID3
    ILI9341_CMD_RDID4      = 0xDD,  // Read ID4 (часто используется для точной идентификации)

    /* --- Коррекция гаммы --- */
    ILI9341_CMD_GMCTRP1    = 0xE0,  // 8.3.24. Positive Gamma Correction (E0h)
    ILI9341_CMD_GMCTRN1    = 0xE1   // Negative Gamma Correction
} Ili9341Cmd_t;

#endif /* ILI9341_CONST_H */
