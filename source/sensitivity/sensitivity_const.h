#ifndef SENSITIVITY_CONST_H
#define SENSITIVITY_CONST_H

/*   Unit  encoding */
typedef enum {
    UNITS_UNDEF = 0x00, /* no unit, no prefix */
    UNITS_METER, /* meter m length */
    UNITS_FOOT, /* foot ft length */
    UNITS_INCH, /* inch in length */
    UNITS_UVI, /* Ultra violet index */
    UNITS_YARD, /* yard yd length */
    UNITS_MILE, /* mile (English) mi length */
    UNITS_GRAM, /* gram g mass */
    UNITS_TON, /* ton (metric) t mass */
    UNITS_SECOND, /* second s time */
    UNITS_MINUTE, /* minute min time */
    UNITS_HOUR, /* hour h time */
    UNITS_DAY, /* day d time */
    UNITS_YEAR, /* year y time */
    UNITS_AMPERE, /* ampere A current */
    UNITS_VOLT, /* volt V voltage */
    UNITS_COULOMB, /* coulomb C electric charge */
    UNITS_OHM, /* ohm W resistance */
    UNITS_FARAD, /* farad F capacitance */
    UNITS_HENRY, /* henry H inductance */
    UNITS_SIEMENS, /* siemens S electric conductance */
    UNITS_WEBER, /* weber Wb magnetic flux */
    UNITS_TESLA, /* tesla T magnetic flux density */
    UNITS_KELVIN, /* kelvin K thermodynamic temperature */
    UNITS_CELSIUS, /* Celsius °C thermodynamic temperature */
    UNITS_FAHRENHEIT, /* Fahrenheit °F thermodynamic temperature */
    UNITS_CANDELA, /* candela cd luminous intensity */
    UNITS_RADIAN, /* radian rad plane angle */
    UNITS_DEGREE, /* degree ° plane angle */
    UNITS_HERTZ, /* hertz Hz frequency */
    UNITS_JOULE, /* joule J energy */
    UNITS_NEWTON, /* Newton N force */
    UNITS_KILOPOND, /* kilopond kp force */
    UNITS_POUND, /* pound force lbf force */
    UNITS_WATT, /* watt W power */
    UNITS_HORSE_POWER, /* horse power (metric) hk power */
    UNITS_HORSE_POWER2, /* horse power (UK and US) hp power */
    UNITS_PASCAL, /* Pascal Pa pressure */
    UNITS_BAR, /* bar bar pressure */
    UNITS_ATMOSPHERE, /* atmosphere atm pressure */
    UNITS_POUND_FORCE_PER_SQUARE, /* pound force per square inch psi pressure */
    UNITS_BECQEREL, /* becqerel Bq radioactivity */
    UNITS_LUMEN, /* lumen lm light flux */
    UNITS_LUX, /* lux lx illuminance */
    UNITS_LITER, /* liter l volume */
    UNITS_GALLON, /* gallon (British) — volume */
    UNITS_GALLON_US, /* gallon (US liq) — volume */
    UNITS_CUBIC_INCH, /* cubic inch cu in volume */
    UNITS_METER_PER_SECOND, /* meter per second m/s speed */
    UNITS_KILOMETRE_PER_HOUR, /* kilometre per hour km/h speed */
    UNITS_MPH, /* mile per hour mph speed */
    UNITS_RPS, /* revolutions per second rps angular velocity */
    UNITS_RPM, /* revolutions per minute rpm angular velocity */
    UNITS_COUNTS, /* counts — — */
    UNITS_PERCENT, /* percent % — */
    UNITS_MG_PER_STROKE, /* milligram per stroke mg/stroke mass per engine stroke */
    UNITS_METER_PER_SQUARE_SECOND, /* meter per square second m/s2 acceleration */
    UNITS_NEWTON_METER, /* Newton meter Nm moment (e.g. torsion moment) */
    UNITS_LITER_PER_MINUTE, /* liter per minute l/min flow */
    UNITS_WATT_PER_SQUARE_METER, /* watt per square meter W/m2 intensity */
    UNITS_BAR_PER_SECOND, /* bar per second bar/s pressure change */
    UNITS_RADIANS_PER_SECOND, /* radians per second rad/s angular velocity */
    UNITS_RADIANS_PER_SQUARE_SECOND, /* radians per square second rad/s2 angular acceleration */
    UNITS_KILOGRAM_PER_SQUARE_METER, /* kilogram per square meter kg/m2 — */

    UNITS_TOTAL, /**/
} Units_t;

typedef enum {
    SCALE_EXA = 18,
    SCALE_PETA = 15,
    SCALE_TERA = 12,
    SCALE_GIGA = 9,
    SCALE_MEGA = 6,
    SCALE_KILO = 3,
    SCALE_HECTO = 2,
    SCALE_DECA = 0,
    SCALE_DECI = -1,
    SCALE_CENTI = -2,
    SCALE_MILLI = -3,
    SCALE_MICRO = -6,
    SCALE_NANO = -9,
    SCALE_PICO = -12,
    SCALE_FEMTO = -15,
    SCALE_ATTO = -18,
    SCALE_UNDEF = 19,
} Scale_t;

/* Physical quantities*/
typedef enum {
    PHY_VARIABLE_UNDEF = 0, /* no unit, */
    /*basic physical quantities*/
    PHY_VARIABLE_LENGTH, /*   length */
    PHY_VARIABLE_MASS, /*   mass */
    PHY_VARIABLE_TIME, /*   time */
    PHY_VARIABLE_CURRENT, /*   current */
    PHY_VARIABLE_LUMINOUS_INTENSITY, /* luminous intensity */
    PHY_VARIABLE_TEMPERATURE, /* temperature */

    PHY_VARIABLE_PLANE_ANGLE, /* plane angle */
    PHY_VARIABLE_RADIOACTIVITY, /* radioactivity */
    /*derived physical quantities*/

    PHY_VARIABLE_ELECTRIC_CHARGE, /*  electric charge */
    PHY_VARIABLE_FORCE, /* force */
    PHY_VARIABLE_RESISTANCE, /*  resistance */
    PHY_VARIABLE_VOLTAGE, /*  voltage */
    PHY_VARIABLE_CAPACITANCE, /*  capacitance */
    PHY_VARIABLE_INDUCTANCE, /*   inductance */
    PHY_VARIABLE_MAGNETIC_FLUX, /*  magnetic flux */
    PHY_VARIABLE_ELECTRIC_CONDUCTANCE, /*  electric conductance */
    PHY_VARIABLE_MAGNETIC_FLUX_DENSITY, /*  magnetic flux density */
    PHY_VARIABLE_ENERGY, /* energy */
    PHY_VARIABLE_POWER, /* power */
    PHY_VARIABLE_LIGHT_FLUX, /* light flux */
    PHY_VARIABLE_ILLUMINANCE, /*illuminance */
    PHY_VARIABLE_COUNTS, /* counts — — */
    PHY_VARIABLE_PERCENT, /* percent % — */
    PHY_VARIABLE_PRESSURE, /* pressure */
    PHY_VARIABLE_ACCELERATION, /* acceleration */
    PHY_VARIABLE_TORSION_MOMENT, /* (e.g. torsion moment) */
    PHY_VARIABLE_FLOW, /* flow */
    PHY_VARIABLE_WATT_PER_SQUARE_METER, /*  intensity */
    PHY_VARIABLE_BAR_PER_SECOND, /* pressure change */
    PHY_VARIABLE_ANGULAR_VELOCITY, /* angular velocity */
    PHY_VARIABLE_FREQUENCY, /* frequency */
    PHY_VARIABLE_SPEED, /*  speed */
    PHY_VARIABLE_SQUARE, /*   length */
    PHY_VARIABLE_VOLUME, /*  volume */

    PHY_VARIABLE_TOTAL,

} PhysicalQuantity_t;

#endif                                                                                       /* SENSITIVITY_CONST_H */
