#include "test_gnss_utils.h"

#ifdef X86_64
#include <stdio.h>
#endif

#include "float_utils.h"
#include "gnss_diag.h"
#include "gnss_utils.h"
#include "log.h"
#include "unit_test_check.h"

bool test_gnss_azimuth(void) {
    LOG_INFO(GNSS, "%s()", __FUNCTION__);
    set_log_level(GNSS, LOG_LEVEL_DEBUG);
    double azimuth = 0.0;
    GnssCoordinate_t rover = {0.0, 0.0};
    GnssCoordinate_t beacon_north = {40.0, 0.0};
    GnssCoordinate_t beacon_south = {-10.0, 0.0};
    GnssCoordinate_t beacon_west = {0.0, -10.0};
    GnssCoordinate_t beacon_east = {0.0, 10.0};
    azimuth = gnss_calc_azimuth_deg(rover, beacon_west);
    ASSERT_TRUE(is_double_equal_absolute(-90.0, azimuth, 0.5));

    azimuth = gnss_calc_azimuth_deg(rover, beacon_north);
    ASSERT_TRUE(is_double_equal_absolute(0.0, azimuth, 0.5));

    azimuth = gnss_calc_azimuth_deg(rover, beacon_south);
    ASSERT_TRUE(is_double_equal_absolute(180.0, azimuth, 0.5));

    azimuth = gnss_calc_azimuth_deg(rover, beacon_east);
    ASSERT_TRUE(is_double_equal_absolute(90.0, azimuth, 0.5));
    return true;
}

bool test_gnss_azimuth1(void) {
    LOG_INFO(GNSS, "%s()", __FUNCTION__);
    set_log_level(GNSS, LOG_LEVEL_DEBUG);
    double azimuth = 0.0;
    GnssCoordinate_t TxNode = {56.388509, 37.396453};
    GnssCoordinate_t RxNode = {56.433870, 37.159016};

    azimuth = gnss_calc_azimuth_deg(RxNode, TxNode);
    LOG_INFO(GNSS, "Az:%f Deg", azimuth);
    ASSERT_TRUE(is_double_equal_absolute(109.05, azimuth, 1.0));
    ASSERT_GR(90.0, azimuth);
    ASSERT_GR(azimuth, 170.0);

    return true;
}

bool test_gnss_compass(void) {
    LOG_INFO(GNSS, "%s()", __FUNCTION__);
    set_log_level(GNSS, LOG_LEVEL_DEBUG);
    ASSERT_STREQ("N", BearingDeg2Str(0.0));
    ASSERT_STREQ("S", BearingDeg2Str(180.0));
    ASSERT_STREQ("E", BearingDeg2Str(90.0));
    ASSERT_STREQ("W", BearingDeg2Str(-90.0));
    ASSERT_STREQ("NW", BearingDeg2Str(-45.0));
    ASSERT_STREQ("NE", BearingDeg2Str(45.0));
    ASSERT_STREQ("SW", BearingDeg2Str(-135.0));
    ASSERT_STREQ("SE", BearingDeg2Str(135.0));
    set_log_level(GNSS, LOG_LEVEL_INFO);
    return true;
}

bool test_gnss_utils(void) {
    LOG_INFO(GNSS, "%s()", __FUNCTION__);
    set_log_level(GNSS, LOG_LEVEL_DEBUG);
    GnssCoordinate_t dot1 = {55.75512120792506, 37.61651447625873}; /*tower s*/
    GnssCoordinate_t dot2 = {55.74891993335733, 37.61263145873993}; /*tower s*/
    double distance_m = gnss_calc_distance_m(dot1, dot2);
    LOG_DEBUG(GNSS, "Distance:%f m", distance_m);
    ASSERT_NEAR(731, distance_m, 10);
    return true;
}

bool test_gnss_types(void) {
    set_log_level(GNSS, LOG_LEVEL_DEBUG);
    ASSERT_EQ(16, sizeof(GnssCoordinate_t));
    ASSERT_EQ(32, sizeof(LinkInfoPayload_t));
    return true;
}
