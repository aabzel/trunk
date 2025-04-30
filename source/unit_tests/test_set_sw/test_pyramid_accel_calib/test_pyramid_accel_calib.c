#include "test_pyramid_accel_calib.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "pyramid_accel_calib.h"
#include "unit_test_check.h"

#define PAC_EPSILONT 0.001
#define PAC_SCALE (1.0 / sqrtf(3.0))

bool test_pyramid_accel_calib_ideal(void) {
    LOG_INFO(PYRAMID_ACCEL_CALIB, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(PYRAMID_ACCEL_CALIB, LOG_LEVEL_DEBUG);

    PyramidAccelCalibHandle_t Calib = {0};
    Calib.A1.dx = PAC_SCALE;
    Calib.A1.dy = PAC_SCALE;
    Calib.A1.dz = -PAC_SCALE;

    Calib.A2.dx = -PAC_SCALE;
    Calib.A2.dy = -PAC_SCALE;
    Calib.A2.dz = PAC_SCALE;

    ASSERT_TRUE(pyramid_accel_calib(&Calib));
    LOG_INFO(PYRAMID_ACCEL_CALIB, "%s", PyramidAccelCalibToStr(&Calib));

    EXPECT_EQ_FLOAT(1.0, Calib.Scale.dx, PAC_EPSILONT);
    EXPECT_EQ_FLOAT(1.0, Calib.Scale.dy, PAC_EPSILONT);
    EXPECT_EQ_FLOAT(1.0, Calib.Scale.dz, PAC_EPSILONT);
    EXPECT_EQ_FLOAT(0.0, Calib.Offset.dx, PAC_EPSILONT);
    EXPECT_EQ_FLOAT(0.0, Calib.Offset.dy, PAC_EPSILONT);
    EXPECT_EQ_FLOAT(0.0, Calib.Offset.dz, PAC_EPSILONT);

    set_log_level(PYRAMID_ACCEL_CALIB, LOG_LEVEL_INFO);
    return res;
}
