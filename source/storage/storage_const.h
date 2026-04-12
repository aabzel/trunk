#ifndef STORAGE_CONST_H
#define STORAGE_CONST_H

#include "storage_dep.h"
#include "storage_file_ids.h"

#define STORAGE_DATA_SIZE 512
#define STORAGE_TYPE_UNDEF_LEN 0xFFFF

typedef enum {
    STORAGE_TYPE_FLASH_FS = 1,
    STORAGE_TYPE_NVRAM_FS = 2,
    STORAGE_TYPE_FAT_FS = 3,
    STORAGE_TYPE_LITTLE_FS = 4,
    STORAGE_TYPE_UNDEF = 0 ,
}StorageVariat_t;

typedef enum {
    TYPE_BOOL = 2,

    TYPE_INT8 = 3,
    TYPE_INT16 = 5,
    TYPE_INT24 = 24,
    TYPE_INT32 = 8,
    TYPE_INT64 = 10,

    TYPE_UINT8 = 1,
    TYPE_UINT16 = 4,
    TYPE_UINT24 = 22,
    TYPE_UINT32 = 6,
    TYPE_UINT32_HEX = 7,
    TYPE_UINT64 = 9,

    TYPE_STRING = 11,
    TYPE_FLOAT = 12,
    TYPE_DOUBLE = 13,
    TYPE_STRUCT = 14,

    /*Conventional Binary Coded Decimal encoding is used to represent two numeric
digits per byte. The upper nibble is used to represent the most significant digit
(0 - 9), and the lower nibble the least significant digit (0 -9). */
    TYPE_BINARY_CODED_DECIMAL = 22,

    TYPE_TIME_DATE = 15,
    TYPE_OPERATION = 16,
    TYPE_ARRAY = 17,
    TYPE_UINT = 18,
    TYPE_INT = 19,
    TYPE_FORMULA = 20,
    TYPE_ENUM= 21,

    /*Bit mapped encoding uses individual bits or small groups of bits to represent status.
      A validity mask is used to indicate the validity of each bit for particular applications.
     */
    TYPE_BIT_MAP = 23,

    TYPE_UNDEF = 0,
} StorageType_t;

typedef enum {
    ACCESS_READ_ONLY = 1, /* Read-only. The bit or bit field can only be read. */
    ACCESS_READ_WRITE = 4, /* Read and write. The bit or bit field can be read and written */
    ACCESS_WRITE_ONLY = 2, /* Write-only. The bit or bit field can only be written. */
    ACCESS_WRITE_CLEAR = 5, /* Write 0 or 1 to clear. The bit or bit field can be written as 0 or 1 to be "cleared." */
    ACCESS_WRITE_0_CLEAR = 5, /* Write 0 to clear. The bit or bit field must be written as 0 to be "cleared." */
    ACCESS_WRITE_1_CLEAR = 6, /* Write 1 to clear. The bit or bit field must be written as 1 to be "cleared." */
    ACCESS_ERASE = 3,

    ACCESS_UNDEF = 0,
} StorageAccess_t;


typedef enum  {
 STORAGE_UNITS_NO_UNIT  =0x00, /*unit,  no  prefix */
 STORAGE_UNITS_METER  =0x1, /* m  Length */
 STORAGE_UNITS_FOOT  =0x2 , /* ft  Length */
 STORAGE_UNITS_INCH  =0x3 , /* in  Length */
 STORAGE_UNITS_YARD  =0x4 , /* yd  Length */
 STORAGE_UNITS_MILE  =0x5 , /* (English)  mi  length */
 STORAGE_UNITS_GRAM  =0x6 , /* g  mass */
 STORAGE_UNITS_TON  =0x7 , /* (metric)  t  mass */
 STORAGE_UNITS_SECOND  =0x8 , /* s  time */
 STORAGE_UNITS_MINUTE  =0x9 , /* min  time */
 STORAGE_UNITS_HOUR  =0xa , /* h  time */
 STORAGE_UNITS_DAY  =0xb , /* d  time */
 STORAGE_UNITS_YEAR  =0xc , /* y  time */
 STORAGE_UNITS_AMPERE  =0xd , /* A  current */
 STORAGE_UNITS_VOLT  =0xe , /* V  voltage */
 STORAGE_UNITS_COULOMB  =0xf , /* C  electric  charge */
 STORAGE_UNITS_OHM  =0x10 , /* W  resistance */
 STORAGE_UNITS_FARAD  =0x11 , /* F  capacitance */
 STORAGE_UNITS_HENRY  =0x12, /* H  inductance */
 STORAGE_UNITS_SIEMENS  =0x13, /* S  electric  conductance */
 STORAGE_UNITS_WEBER  =0x14, /* Wb  magnetic  flux */
 STORAGE_UNITS_TESLA  =0x15, /* T  magnetic  flux  density */
 STORAGE_UNITS_KELVIN  =0x16, /* K  thermodynamic  temperature */
 STORAGE_UNITS_CELSIUS  =0x17, /* �C  thermodynamic  temperature */
 STORAGE_UNITS_FAHRENHEIT  =0x18 , /* �F  thermodynamic  temperature */
 STORAGE_UNITS_CANDELA  =0x19, /* cd  luminous  intensity */
 STORAGE_UNITS_RADIAN  =0x1a, /* rad  plane  angle */
 STORAGE_UNITS_DEGREE  =0x1b, /* �  plane  angle */
 STORAGE_UNITS_HERTZ  =0x1c, /* Hz  frequency */
 STORAGE_UNITS_JOULE  =0x1d, /* J  energy */
 STORAGE_UNITS_NEWTON  =0x1e, /* N  force */
 STORAGE_UNITS_KILOPOND  =0x1f, /* kp  force */
 STORAGE_UNITS_POUND  =0x20, /* force  lbf  force */
 STORAGE_UNITS_WATT  =0x21, /* W  power */
 STORAGE_UNITS_HORSE_POWER_HK  =0x22, /* power  (metric)  hk  power */
 STORAGE_UNITS_HORSE_POWER_HP  =0x23, /* power  (UK  and *S)  hp  power */
 STORAGE_UNITS_PASCAL  =0x24, /* Pa  pressure */
 STORAGE_UNITS_BAR  =0x25, /* bar  pressure */
 STORAGE_UNITS_ATMOSPHERE  =0x26, /* atm  pressure */
 STORAGE_UNITS_POUND_FORCE_PER_SQUARE_INCH   =0x27, /* force  per  square  inch  psi  pressure */
 STORAGE_UNITS_BECQEREL  =0x28, /* Bq  radioactivity */
 STORAGE_UNITS_LUMEN  =0x29, /* lm  light  flux */
 STORAGE_UNITS_LUX  =0x2a, /* lx  illuminance */
 STORAGE_UNITS_LITER  =0x2b, /* l  volume */
 STORAGE_UNITS_GALLON_BRITISH  =0x2c, /* (British)  ---  volume */
 STORAGE_UNITS_GALLON_US  =0x2d, /* (US  liq)  ---  volume */
 STORAGE_UNITS_CUBIC_INCH  =0x2e, /* inch  cu  in  volume */
 STORAGE_UNITS_METER_PER_SECOND  =0x2f, /* per  second  m/s  speed */
 STORAGE_UNITS_KILOMETER_PER_HOUR  =0x30, /* per  hour  km/h  speed */
 STORAGE_UNITS_MILE_PER_HOUR  =0x31, /* per  hour  mph  speed */
 STORAGE_UNITS_REVOLUTIONS_PER_SECOND  =0x32, /* per  second  rps  angular  velocity */
 STORAGE_UNITS_REVOLUTIONS_PER_MINUTE  =0x33, /* per  minute  rpm  angular  velocity */
 STORAGE_UNITS_COUNTS  =0x34, /* ---  --- */
 STORAGE_UNITS_PERCENT  =0x35, /* %  --- */
 STORAGE_UNITS_MILLIGRAM_PER_STROKE  =0x36, /* per  stroke  mg/stroke  mass  per  engine  stroke */
 STORAGE_UNITS_METER_PER_SQUARE_SECOND  =0x37, /* per  square  second  m/sP2 acceleration */
 STORAGE_UNITS_NEWTON_METER  =0x38, /* meter  Nm  moment  (e.g.  torsion  moment) */
 STORAGE_UNITS_LITER_PER_MINUTE  =0x39, /* per  minute  l/min  flow */
 STORAGE_UNITS_WATT_PER_SQUARE_METER  =0x3a, /* per  square  meter */
 STORAGE_UNITS_BAR_PER_SECOND  =0x3b, /* per  second  bar/s  Pressure  change */
 STORAGE_UNITS_RADIANS_PER_SECOND  =0x3c, /* per  second  rad/s  Angular  velocity */
 STORAGE_UNITS_RADIANS_PER_SQUARE_SECOND  =0x3d, /* per  square  second  rad/sP2 */
 STORAGE_UNITS_KILOGRAM_PER_SQUARE_METER  =0x3e, /* per  square  meter  kg/mP2 */
 STORAGE_UNITS_DATE1  =0x50, /* -  Year-Month-Day */
 STORAGE_UNITS_DATE2  =0x51, /* -  Day/Month/Year */
 STORAGE_UNITS_DATE3  =0x52, /* -  Month/Day/Year */
 STORAGE_UNITS_WEEK  =0x53, /* W  calendar  week */
 STORAGE_UNITS_TIME1  =0x54, /* --- TC  Hour/Minute/Second */
 STORAGE_UNITS_TIME2  =0x55, /* ---  Hour/Minute/Second */
 STORAGE_UNITS_DATEANDTIME1  =0x56, /* ---  Second/Minute/Hour/Day/Month/Year */
 STORAGE_UNITS_DATEANDTIME2  =0x57, /* ---  Second/Minute/Hour/Day/Month/Year/Local  minute  offset/Local  hour  offset */
 STORAGE_UNITS_DATEANDTIME3  =0x58, /* ---  Second/Minute/Hour/Month/Day/Year */
 STORAGE_UNITS_DATEANDTIME4  =0x59,
 STORAGE_UNITS_UNDEF  =0x60, /**/
}StorageUnits_t;


typedef enum {
    STORAGE_PHYSICAL_QUANTITY_LENGTH = 1 ,
    STORAGE_PHYSICAL_QUANTITY_SPEED = 2 ,
    STORAGE_PHYSICAL_QUANTITY_ANGULAR_VELOCITY = 3 ,
    STORAGE_PHYSICAL_QUANTITY_MASS = 4 ,
    STORAGE_PHYSICAL_QUANTITY_TIME = 5 ,
    STORAGE_PHYSICAL_QUANTITY_CURRENT = 6 ,
    STORAGE_PHYSICAL_QUANTITY_VOLTAGE = 7,
    STORAGE_PHYSICAL_QUANTITY_PRESSURE = 8,
    STORAGE_PHYSICAL_QUANTITY_NO = 9 ,
    STORAGE_PHYSICAL_QUANTITY_FLOW  ,
    STORAGE_PHYSICAL_QUANTITY_ANGLE ,
    STORAGE_PHYSICAL_QUANTITY_RADIOACTIVITY ,
    STORAGE_PHYSICAL_QUANTITY_MAGNETIC_FLUX_DENSITY ,
    STORAGE_PHYSICAL_QUANTITY_ELECTRIC_CHARGE ,
    STORAGE_PHYSICAL_QUANTITY_ILLUMINANCE ,
    STORAGE_PHYSICAL_QUANTITY_RESISTANCE ,
    STORAGE_PHYSICAL_QUANTITY_CAPACITANCE ,
    STORAGE_PHYSICAL_QUANTITY_VOLUME ,
    STORAGE_PHYSICAL_QUANTITY_TORQUE ,
    STORAGE_PHYSICAL_QUANTITY_LIGHT_FLUX ,
    STORAGE_PHYSICAL_QUANTITY_FREQUENCY ,
    STORAGE_PHYSICAL_QUANTITY_INDUCTANCE ,
    STORAGE_PHYSICAL_QUANTITY_ELECTRIC_CONDUCTANCE ,
    STORAGE_PHYSICAL_QUANTITY_TEMPERATURE ,
    STORAGE_PHYSICAL_QUANTITY_PRESSURE_CHANGE ,
    STORAGE_PHYSICAL_QUANTITY_MAGNETIC_FLUX ,
    STORAGE_PHYSICAL_QUANTITY_ENERGY ,
    STORAGE_PHYSICAL_QUANTITY_LUMINOUS_INTENSITY ,
    STORAGE_PHYSICAL_QUANTITY_FORCE ,
    STORAGE_PHYSICAL_QUANTITY_POWER ,

    STORAGE_PHYSICAL_QUANTITY_UNDEF = 0 ,
}StoragePhysicalQuantity_t;

/* scale format for real numbers */
typedef enum {
    STORAGE_SCALE_EXA   = 18 ,   /*   exa (prefix) E 1018 U   */
    STORAGE_SCALE_PETA  = 15 ,   /*   peta (prefix) P 1015 U   */
    STORAGE_SCALE_TERA  = 12 ,   /*   tera (prefix) T 1012 U   */
    STORAGE_SCALE_GIGA  = 9 ,   /*    giga (prefix) G 109 U   */
    STORAGE_SCALE_MEGA  = 6 ,   /*    mega (prefix) M 106 U   */
    STORAGE_SCALE_KILO  = 3 ,   /*    kilo (prefix) k 103 U   */
    STORAGE_SCALE_HECTO = 2 ,   /*    hecto (prefix) h 102 U   */
    STORAGE_SCALE_DECA  = 1 ,   /*    deca (prefix) da 10   */
    STORAGE_SCALE_DECI  =-1 ,   /*    deci (prefix) d 10-1 U   */
    STORAGE_SCALE_CENTI =-2 ,   /*    centi (prefix) c 10-2 U   */
    STORAGE_SCALE_MILLI =-3 ,   /*    milli (prefix) m 10-3 U   */
    STORAGE_SCALE_MICRO =-6 ,   /*    micro (prefix) m 10-6 U   */
    STORAGE_SCALE_NANO  =-9 ,   /*    nano (prefix) n 10-9 U   */
    STORAGE_SCALE_PICO  =-12 ,   /*   pico (prefix) p 10-12 U   */
    STORAGE_SCALE_FEMTO =-15 ,   /*   femto (prefix) f 10-15 U    */
    STORAGE_SCALE_ATTO  =-18 ,   /*   atto (prefix) a 10-18   */
    STORAGE_SCALE_ONES  = 0 ,
    STORAGE_SCALE_UNDEF  = 0xFF ,
}StorageScale_t;

#endif /* STORAGE_CONST_H */
