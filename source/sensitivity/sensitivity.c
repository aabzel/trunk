#include "sensitivity.h"

#include <stddef.h>

#include "std_includes.h"
#include "macro_utils.h"

static const PhysicalQuantityInfo_t PhysicalQuantityInfo[] = {
    {
        .units = UNITS_METER,
        .physical_quantity = PHY_VARIABLE_LENGTH,
        .valid = true,
    },
    {
        .units = UNITS_FOOT,
        .physical_quantity = PHY_VARIABLE_LENGTH,
        .valid = true,
    },
    {
        .units = UNITS_INCH,
        .physical_quantity = PHY_VARIABLE_LENGTH,
        .valid = true,
    },
    {
        .units = UNITS_MILE,
        .physical_quantity = PHY_VARIABLE_LENGTH,
        .valid = true,
    },
    {
        .units = UNITS_YARD,
        .physical_quantity = PHY_VARIABLE_LENGTH,
        .valid = true,
    },
    {
        .units = UNITS_GRAM,
        .physical_quantity = PHY_VARIABLE_MASS,
        .valid = true,
    },
    {
        .units = UNITS_LITER,
        .physical_quantity = PHY_VARIABLE_VOLUME,
        .valid = true,
    },
    {
        .units = UNITS_SECOND,
        .physical_quantity = PHY_VARIABLE_TIME,
        .valid = true,
    },
    {
        .units = UNITS_AMPERE,
        .physical_quantity = PHY_VARIABLE_CURRENT,
        .valid = true,
    },
    {
        .units = UNITS_CELSIUS,
        .physical_quantity = PHY_VARIABLE_TEMPERATURE,
        .valid = true,
    },
    {
        .units = UNITS_BECQEREL,
        .physical_quantity = PHY_VARIABLE_RADIOACTIVITY,
        .valid = true,
    },
    {
        .units = UNITS_VOLT,
        .physical_quantity = PHY_VARIABLE_VOLTAGE,
        .valid = true,
    },
    {
        .units = UNITS_FARAD,
        .physical_quantity = PHY_VARIABLE_CAPACITANCE,
        .valid = true,
    },
    {
        .units = UNITS_WATT,
        .physical_quantity = PHY_VARIABLE_POWER,
        .valid = true,
    },
#if 0
      // TODO
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_ENERGY, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_PLANE_ANGLE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_ELECTRIC_CHARGE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_FORCE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_RESISTANCE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_INDUCTANCE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_MAGNETIC_FLUX, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_ELECTRIC_CONDUCTANCE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_MAGNETIC_FLUX_DENSITY, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_LIGHT_FLUX, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_LUMINOUS_INTENSITY, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_ILLUMINANCE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_COUNTS, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_PERCENT, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_PRESSURE, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_ACCELERATION, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_TORSION_MOMENT, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_FLOW, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_WATT_PER_SQUARE_METER, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_BAR_PER_SECOND, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_ANGULAR_VELOCITY, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_FREQUENCY, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_SPEED, .valid = true, },
      { .units = UNITS_, .physical_quantity =PHY_VARIABLE_SQUARE, .valid = true, },
#endif
};

PhysicalQuantityInfo_t* UnitsToPhysicalQuantityInfo(const Units_t units) {
    PhysicalQuantityInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(PhysicalQuantityInfo);
    for(i = 0; i < cnt; i++) {
        if(units == PhysicalQuantityInfo[i].units) {
            Info = &PhysicalQuantityInfo[i];
            break;
        }
    }
    return Info;
}

PhysicalQuantity_t units_to_physical_quantity(const Units_t units) {
    PhysicalQuantity_t physical_quantity = PHY_VARIABLE_UNDEF;
    PhysicalQuantityInfo_t* Info = UnitsToPhysicalQuantityInfo(units);
    if(Info) {
        physical_quantity = Info->physical_quantity;
    }
    return physical_quantity;
}
