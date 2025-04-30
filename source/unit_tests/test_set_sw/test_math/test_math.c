#include "test_math.h"

#include <stdio.h>
#include <time.h>

#include "vector_math.h"

#include "float_utils.h"
#include "time_mcal.h"
#include "unit_test_check.h"
#include "utils_math.h"

bool test_math_powi(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_EQ_U64(4294967296, int_pow(2, 32));
    ASSERT_EQ_U64(256, int_pow(2, 8));
    ASSERT_EQ_U64(65536, int_pow(2, 16));
    ASSERT_EQ_U64(16777216, int_pow(2, 24));
    ASSERT_EQ_U64(1, int_pow(2, 0));
    ASSERT_EQ_U64(2, int_pow(2, 1));
    ASSERT_EQ(1, ipow(2, 0));
    ASSERT_EQ(2, ipow(2, 1));
    ASSERT_EQ(32, ipow(2, 5));
    ASSERT_EQ(4096, ipow(2, 12));
    return res;
}

static bool test_math_sin_1hz(double time_s, double exp) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(MATH, LOG_LEVEL_DEBUG);
    double val = calc_sin_sample(SEC_2_USEC(time_s), 1.0, 0.0, 500.0, 0.0);
    set_log_level(MATH, LOG_LEVEL_INFO);
    bool res = is_double_equal_absolute(exp, val, 10.0);
    ASSERT_TRUE(res);
    return res;
}

bool test_math_sin(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(MATH, LOG_LEVEL_DEBUG);
    bool res = true;

    ASSERT_TRUE(test_math_sin_1hz(0.0, 0.0));
    ASSERT_TRUE(test_math_sin_1hz(0.25, 500.0));
    ASSERT_TRUE(test_math_sin_1hz(0.5, 0.0));
    ASSERT_TRUE(test_math_sin_1hz(0.75, -500.0));
    ASSERT_TRUE(test_math_sin_1hz(1.0, 0.0));

    set_log_level(MATH, LOG_LEVEL_INFO);
    return res;
}

bool test_math_period(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(100, freq2period_ms(0.0));
    ASSERT_EQ(2000, freq2period_ms(0.5));
    ASSERT_EQ(1000, freq2period_ms(1.0));
    ASSERT_EQ(500, freq2period_ms(2.0));
    return res;
}

bool test_math_double(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    long double value = 2345678901234568192.0;
    LOG_INFO(TEST, "val %f", value);
    value *= 10.0;
    LOG_INFO(TEST, "val*10 %f", value);
    ASSERT_NEAR(23456789012345681920.0, value, 0.0001);
    return res;
}

bool test_math_double2(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    char lText[80] = "";
    double value = 23456789012345678901.0;
    sprintf(lText, "sprintf ConstVal Le %Le", (long double)23456789012345678901.0);
    LOG_INFO(TEST, "%s", lText);

    sprintf(lText, "sprintf ConstVal Lf %Lf", (long double)23456789012345678901.0);
    LOG_INFO(TEST, "%s", lText);

    sprintf(lText, "sprintf ConstVal f %f", (long double)23456789012345678901.0);
    LOG_INFO(TEST, "%s", lText);

    LOG_INFO(TEST, "Constval f %f", (long double)23456789012345678901.0);
    // LOG_INFO(TEST, "Constval L %L",(long double) 23456789012345678901.0);
    LOG_INFO(TEST, "ConstVal Lf %Lf", (long double)23456789012345678901.0);
    LOG_INFO(TEST, "ConstVal Le %Le", (long double)23456789012345678901.0);

    sprintf(lText, "sprintf ConstVal f %f", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal F %F", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal lf %lf", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal Lf %Lf", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal e %e", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal E %E", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal G %G", value);
    LOG_INFO(TEST, "%s", lText);
    sprintf(lText, "sprintf ConstVal g %g", value);
    LOG_INFO(TEST, "%s", lText);

    LOG_INFO(TEST, "val f %f", value);
    LOG_INFO(TEST, "val F %F", value);
    LOG_INFO(TEST, "val lf %lf", value);
    LOG_INFO(TEST, "val Lf %Lf", value);
    LOG_INFO(TEST, "val e %e", value);
    LOG_INFO(TEST, "val E %E", value);
    LOG_INFO(TEST, "val G %G", value);
    LOG_INFO(TEST, "val g %g", value);
    ASSERT_GR(234567890123456789.0, value);
    ASSERT_GR(value, 234567890123456789010.0);
    return res;
}
/*
https://www.exploringbinary.com/twos-complement-converter/
*/

static bool test_math_vectors_angle_one_complex(double expected_angle_rad, double a_x, double a_y, double b_x,
                                                double b_y) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
#ifdef HAS_MATH_VECTOR
    double angle_deg = 0;
    // double angle_rad=0;
    double complex_angle_deg = 0;
    // double complex_angle_rad=0;

    Vector_t v1 = {0};
    Vector_t v2 = {0};
    v1.dx = a_x;
    v1.dy = a_y;
    v1.dz = 0;
    v2.dx = b_x;
    v2.dy = b_y;
    v2.dz = 0;
    angle_deg = calc_angle_between_vectors_deg(&v1, &v2);
    LOG_DEBUG(MATH, "Theta:%f deg", angle_deg);

    ASSERT_EQ_DOUBLE(expected_angle_rad, angle_deg)
    double complex X1 = a_x + a_y * I;
    double complex X2 = b_x + b_y * I;
    // complex_angle_rad= calc_angle_between_complex_rad(&X1,&X2 );
    complex_angle_deg = calc_angle_between_complex_deg(&X1, &X2);
    ASSERT_EQ_DOUBLE(angle_deg, complex_angle_deg)
#endif
    return res;
}

static bool test_math_vectors_angle_one(double expected_angle_deg, double a_x, double a_y, double b_x, double b_y) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
#ifdef HAS_MATH_VECTOR
    double angle_deg = 0;
    // double angle_rad=0;
    // double complex_angle_deg = 0;
    // double complex_angle_rad=0;

    Vector_t v1 = {0};
    Vector_t v2 = {0};
    v1.dx = a_x;
    v1.dy = a_y;
    v1.dz = 0;
    v2.dx = b_x;
    v2.dy = b_y;
    v2.dz = 0;
    angle_deg = calc_angle_between_vectors_deg(&v1, &v2);
    LOG_DEBUG(MATH, "Theta:%f deg", angle_deg);

    ASSERT_EQ_DOUBLE(expected_angle_deg, angle_deg)

#endif
    return res;
}

// tsr math_vectors_angle
bool test_math_vectors_angle(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(MATH, LOG_LEVEL_DEBUG);
    EXPECT_TRUE(test_math_vectors_angle_one_complex(-135.0, 1.0, 0.0, -1.0, -1.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(135.0, 1.0, 0.0, -1.0, 1.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(-45.0, 1.0, 0.0, 1.0, -1.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(45.0, 1.0, 0.0, 1.0, 1.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(-90.0, 0.0, 1.0, 1.0, 0.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(90.0, 1.0, 0.0, 0.0, 1.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(0.0, 1.0, 1.0, 1.0, 1.0));
    EXPECT_TRUE(test_math_vectors_angle_one_complex(180.0, 1.0, 0.0, -1.0, 0.0));

    set_log_level(MATH, LOG_LEVEL_INFO);
    return res;
}

bool test_math_vectors_angle_same_abs(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(MATH, LOG_LEVEL_DEBUG);
    EXPECT_TRUE(test_math_vectors_angle_one(0.0, -1220.0, -44.0, -1220.0, -44.0));

    EXPECT_TRUE(test_math_vectors_angle_one(90.0, 1.0, 0.0, 0.0, 1.0));
    EXPECT_TRUE(test_math_vectors_angle_one(90.0, 1.0, 0.0, 0.0, 10.0));

    set_log_level(MATH, LOG_LEVEL_INFO);
    return res;
}

bool test_math_vectors_angle_same_angle(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
#ifdef HAS_MATH_VECTOR
    set_log_level(MATH, LOG_LEVEL_DEBUG);

    Vector_t v1 = {0};
    v1.dx = 4;
    v1.dy = 5;
    v1.dz = 0;

    double angle_deg = 0;
    angle_deg = calc_angle_between_vectors_deg(&v1, &v1);
    LOG_DEBUG(MATH, "Theta:%f deg", angle_deg);

    ASSERT_EQ_DOUBLE(0.0, angle_deg)

    set_log_level(MATH, LOG_LEVEL_INFO);
#endif
    return res;
}
