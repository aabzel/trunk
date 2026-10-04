#include "pyramid_accel_calib_config.h"

#include "data_utils.h"
#include "pyramid_accel_calib_types.h"

const PyramidAccelCalibConfig_t PyramidAccelCalibConfig[] = { { .num = 1, .name = "ForLIS3DHYG",
        .valid = true,
        .Scale = {
                .dx = 1.0,
                .dy = 1.0,
                .dz = 1.0, },
        .Offset = {
                .dx = 0.0,
                .dy = 0.0,
                .dz = 0.0, },
},
        { .num = 2,
                .name = "ForTests",
                .valid = true,
                .Scale = {
        .dx = 1.0,
        .dy = 1.0,
        .dz = 1.0, },
        .Offset = { .dx = 0.0,
                .dy = 0.0,
                .dz = 0.0,
        },
        },
};

PyramidAccelCalibHandle_t PyramidAccelCalibInstance[] = {
        { .num = 1, .valid = true, },
        { .num = 2,
        .valid = true, } };

uint32_t pyramid_accel_calib_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(PyramidAccelCalibConfig);
    return cnt;
}
