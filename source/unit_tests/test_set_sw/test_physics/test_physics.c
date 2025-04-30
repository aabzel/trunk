

#include "test_physics.h"

#include "physics_utils.h"
#include "log.h"
#include "unit_test_check.h"
#include "time_mcal.h"
#ifdef HAS_CLOCK
#include "clock_utils.h"
#endif

#ifndef GHZ_TO_HZ
#define GHZ_TO_HZ(HZ) ( (uint64_t) (  ( (double)(HZ) )*1000000000.0  ) )
#endif

bool test_physics_timer_2_sec(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    double tof_s = 0.0;
    double tof_ns = 0.0;

    tof_s = TIMER_2_SECONDS( 20,  GHZ_TO_HZ(64));
    tof_ns=SEC_2_NSEC(tof_s);
    ASSERT_EQ_DOUBLE(0.3125, tof_ns);

    tof_s = TIMER_2_SECONDS( 88,  GHZ_TO_HZ(64));
    tof_ns=SEC_2_NSEC(tof_s);
    ASSERT_EQ_DOUBLE(1.375, tof_ns);

    tof_s = TIMER_2_SECONDS( 888,  GHZ_TO_HZ(64));
    tof_ns = SEC_2_NSEC(tof_s);
    ASSERT_EQ_DOUBLE(13.875, tof_ns);

    return res;
}

bool test_physics_timer_to_dist(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    double dist_ms = 0.0;

    dist_ms = physics_timer_to_dist(  88, GHZ_TO_HZ(64));
    ASSERT_EQ_DOUBLE(0.412091002125, dist_ms);

    dist_ms = physics_timer_to_dist(  888, GHZ_TO_HZ(64));
    ASSERT_EQ_DOUBLE(4.158372839625, dist_ms);

    return res;
}

