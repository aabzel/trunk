#include "physics_commands.h"

#include <math.h>

#include "convert.h"
#include "convert.h"
#include "log.h"
#include "num_to_str.h"
#include "physics_utils.h"

/*
 plcl 335 1u

  plcl 1562 0.976u
  plcl 7353 0.976u

 */
bool phy_lc_loop_calc_l_command(int32_t argc, char* argv[]) {
    bool res = false;
    double f0_freq_hz = 335.0;
    double capasity_farad = 1.0 * pow(10.0, -6.0);

    if (2 == argc) {
        res = try_str2number(argv[0], &f0_freq_hz);
        res = try_str2number(argv[1], &capasity_farad) && res;

    }
    if (res) {

        double inductance = physics_lc_loop_calc_inductance(f0_freq_hz, capasity_farad);

        LOG_INFO(PHYSICS, "F0:%s Hz", DoubleToStr(f0_freq_hz));
        LOG_INFO(PHYSICS, "C:%s F", DoubleToStr(capasity_farad));
        LOG_INFO(PHYSICS, "L:%s H", DoubleToStr(inductance));
    }else{
        LOG_ERROR(PHYSICS, "plcl F C");

    }
    return res;
}
