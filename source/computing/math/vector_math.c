#include "vector_math.h"

#include <complex.h>
#include <math.h>
#include <string.h>

//#include "float_utils.h"
#include "float_utils.h"
#include "log.h"
#include "utils_math.h"
#include "vector_diag.h"

float norm_f(const VectorF_t* const Node) {
    float norm = 0.0;
    if(Node) {
        float argument = ((Node->dx) * (Node->dx)) + ((Node->dy) * (Node->dy)) + ((Node->dz) * (Node->dz));
        norm = sqrtf(argument);
    }
    return norm;
}

static float dot_product_f(const VectorF_t* const v1, const VectorF_t* const v2) {
    float scalar_product = 0.0;
    scalar_product = (v1->dx) * (v2->dx) + (v1->dy) * (v2->dy) + (v1->dz) * (v2->dz);
    return scalar_product;
}

float norm_d(const VectorF_t* const Node) {
    float norm = 0.0;
    if(Node) {
        float argument = ((Node->dx) * (Node->dx)) + ((Node->dy) * (Node->dy)) + ((Node->dz) * (Node->dz));
        norm = sqrt(argument);
    }
    return norm;
}

static float dot_product_d(const VectorF_t* const v1, const VectorF_t* const v2) {
    float dot = 0.0;
    dot = (v1->dx) * (v2->dx) + (v1->dy) * (v2->dy) + (v1->dz) * (v2->dz);
    return dot;
}

VectorF_t init_vector(float dx, float dy, float dz) {
    VectorF_t vec_out;
    vec_out.dx = dx;
    vec_out.dy = dy;
    vec_out.dz = dz;
    return vec_out;
}

Dot_t init_dot(float x, float y, float z) {
    Dot_t dot_out;
    dot_out.x = x;
    dot_out.y = y;
    dot_out.z = z;
    return dot_out;
}

static VectorF_t cross(const VectorF_t* const a, const VectorF_t* const b) {
    VectorF_t v;
    v.dx = a->dy * b->dz - a->dz * b->dy;
    v.dy = -(a->dx * b->dz - a->dz * b->dx);
    v.dz = a->dx * b->dy - a->dy * b->dx;
    return v;
}

static float mySign(float val) {
    if(0.0 < val) {
        return 1.0;
    }
    if(val < 0.0) {
        return -1.0;
    }
    return 0.0;
}

float calc_angle_between_3d_f_vectors_rad(const VectorF_t* const v1, const VectorF_t* const v2) {
    float abs_betta_rad = 0.0f;
    float norm1 = norm_f(v1);
    float norm2 = norm_f(v2);
    bool res1 = float_is_zero(norm1);
    bool res2 = float_is_zero(norm2);
    LOG_DEBUG(VECTOR_MATH, "Norn1:%f,Norm2:%f", norm1, norm2);
    if(res1 || res2) {
        abs_betta_rad = 0.0f;
    } else {
        float scalar_product = dot_product_f(v1, v2);
        LOG_DEBUG(VECTOR_MATH, "DotProd:%f", scalar_product);
        float acos_arg = scalar_product / (norm1 * norm2);
        LOG_DEBUG(VECTOR_MATH, "acos_arg:%f", acos_arg);
        bool res = is_float_equal_absolute(1.0, acos_arg, ACOS_ARG_ERROR);
        if(res) {
            abs_betta_rad = 0.0f;
        } else {
            abs_betta_rad = acosf(acos_arg);
        }
    }

    return abs_betta_rad;
}

#if 0
float calc_angle_between_vectors_naiv_rad(const VectorF_t* const v1, const VectorF_t* const v2) {
    float arg_diff_rad = 0.0;
    LOG_DEBUG(VECTOR_MATH, "V1:%s", VectorToStr(v1));
    LOG_DEBUG(VECTOR_MATH, "V2:%s", VectorToStr(v2));

    float complex X1 = v1->dx - v1->dy * I;
    float complex X2 = v2->dx - v2->dy * I;

    if(cabs(X1)) {
        if(cabs(X2)) {
            float x1_arg_rad = carg(X1);
            float x2_arg_rad = carg(X2);

            arg_diff_rad = x1_arg_rad - x2_arg_rad;
            if(M_PI < arg_diff_rad) {
                arg_diff_rad = arg_diff_rad - M_2_PI;
            } else {
                if(arg_diff_rad < -M_PI) {
                    arg_diff_rad = arg_diff_rad + M_2_PI;
                }
            }
        }
    }

    LOG_DEBUG(VECTOR_MATH, "Theta:%f rad", arg_diff_rad);
    return arg_diff_rad;
}
#endif

/**/
float calc_angle_between_vectors_rad(const VectorF_t* const v1_in, const VectorF_t* const v2_in) {
    float norm1 = 0.0;
    float norm2 = 0.0;
    float absBetta_rad = 0.0;
    float betta_rad = 0.0;
    LOG_DEBUG(VECTOR_MATH, "V1:%s", VectorToStr(v1_in));
    LOG_DEBUG(VECTOR_MATH, "V2:%s", VectorToStr(v2_in));
    bool calc_need = true;
    VectorF_t v1 = {0};
    VectorF_t v2 = {0};
    memcpy(&v1, v1_in, sizeof(VectorF_t));
    memcpy(&v2, v2_in, sizeof(VectorF_t));

    float dotPproduct = 0.0;
    VectorF_t v3 = {0};
    norm1 = norm_d(&v1);
    norm2 = norm_d(&v2);
    LOG_DEBUG(VECTOR_MATH, "Norn1:%f,Norm2:%f", norm1, norm2);
    bool res1 = float_is_zero(norm1);
    if(res1) {
        LOG_ERROR(VECTOR_MATH, "Norm1,Zero");
        // v1.dx = 1.0;
        // norm1 = norm_d(&v1);
        // res1 = false;
        betta_rad = 0.0;
        calc_need = false;
    }

    bool res2 = float_is_zero(norm2);
    if(res2) {
        LOG_DEBUG(VECTOR_MATH, "Norm2,Zero");
        // v2.dx = 1.0;
        // norm2 = norm_d(&v2);
        //   res2 = false;
        betta_rad = 0.0;
        calc_need = false;
    }

    if(calc_need) {
        dotPproduct = dot_product_d(&v1, &v2);
        LOG_DEBUG(VECTOR_MATH, "DotProd:%f", dotPproduct);

        float acos_arg = dotPproduct / (norm1 * norm2);
        LOG_DEBUG(VECTOR_MATH, "acos_arg:%f", acos_arg);
        bool res = is_float_equal_absolute(1.0, acos_arg, ACOS_ARG_ERROR);
        if(res) {
            LOG_DEBUG(VECTOR_MATH, "V1:%s", VectorToStr(v1_in));
            LOG_DEBUG(VECTOR_MATH, "V2:%s", VectorToStr(v2_in));
            LOG_DEBUG(VECTOR_MATH, "Acos,Arg,Err:%10.9f", acos_arg);
            betta_rad = 0.0f;
        } else {
            /*-1 ....1 */
            absBetta_rad = acosf(acos_arg);
            // scalar multiplication gives just module of  the angle.
            // vector multiplication gives the sign of the angle.
            v3 = cross(&v1, &v2);
            if(float_is_zero(v3.dx) && float_is_zero(v3.dy) && float_is_zero(v3.dz)) {
                betta_rad = absBetta_rad;
            } else {
                betta_rad = mySign(v3.dz) * absBetta_rad;
            }
        }
    }
    LOG_DEBUG(VECTOR_MATH, "AbsTheta:%f Rad,Theta:%f Rad", absBetta_rad, betta_rad);
    return betta_rad;
}

float calc_angle_between_vectors_deg(const VectorF_t* const v1, const VectorF_t* const v2) {
    float angle_deg = 0.0f;
    float angle_rad = 0.0f;
    angle_rad = calc_angle_between_vectors_rad(v1, v2);

    angle_deg = rad_2_deg(angle_rad);
    LOG_DEBUG(VECTOR_MATH, "Angle:%f rad=%f deg", angle_rad, angle_deg);
    return angle_deg;
}

#if 0
float calc_angle_between_vectors_naiv_deg(const VectorF_t* const v1, const VectorF_t* const v2) {
    float angle_deg = 0.0;
    float angle_rad = 0.0;
    angle_rad = calc_angle_between_vectors_naiv_rad(v1, v2);
    angle_deg = rad_2_deg(angle_rad);
    return angle_deg;
}
#endif

float deg2radians(float degrees) {
    const float pi_on_180 = 4.0 * atan(1.0) / 180.0;
    return degrees * pi_on_180;
}

float radians2deg(float radians) { return ((radians * 180.0) / M_PI); }
float radians2deg_f(float radians) { return ((radians * 180.0) / M_PI); }

Dot_t get_line_end(Line_t in_line) {
    Dot_t end_point;
    end_point.x = in_line.start.x + in_line.vector.dx;
    end_point.y = in_line.start.y + in_line.vector.dy;
    end_point.z = in_line.start.z + in_line.vector.dz;
    return end_point;
}

static VectorF_t compose_vector_from_2dot(Dot_t da, Dot_t db) {
    VectorF_t out_vec;
    out_vec.dx = db.x - da.x;
    out_vec.dy = db.y - da.y;
    out_vec.dz = db.z - da.z;
    return out_vec;
}

static bool is_signe_different(float a, float b) {
    if((a < 0) && (0 < b)) {
        return true;
    }
    if((b < 0) && (0 < a)) {
        return true;
    }
    return false;
}

bool is_line_segment_crossed(Line_t* line_a, Line_t* line_b) {
    bool res = false;
#ifdef DEBUG_VECTOR_CALC
    LOG_DEBUG(VECTOR_MATH, "\n%s()", __FUNCTION__);
#endif
    Dot_t a_start, b_start;
    a_start.x = line_a->start.x;
    a_start.y = line_a->start.y;
    a_start.z = line_a->start.z;
    Dot_t a_end = get_line_end(*line_a);

    b_start.x = line_b->start.x;
    b_start.y = line_b->start.y;
    b_start.z = line_b->start.z;

    Dot_t b_end = get_line_end(*line_b);
#ifdef DEBUG_VECTOR_CALC
    print_dot(a_start, "a_start");
    print_dot(a_end, "a_end");
    print_dot(b_start, "b_start");
    print_dot(b_end, "b_end");
#endif

    VectorF_t a_st_b_st = compose_vector_from_2dot(a_start, b_start);
    VectorF_t a_st_b_en = compose_vector_from_2dot(a_start, b_end);
    VectorF_t b_st_a_st = compose_vector_from_2dot(b_start, a_start);
    VectorF_t b_st_a_en = compose_vector_from_2dot(b_start, a_end);
#ifdef DEBUG_VECTOR_CALC
    print_vector(a_st_b_en, "a_st_b_en");
    print_vector(a_st_b_st, "a_st_b_st");
    print_vector(b_st_a_st, "b_st_a_st");
    print_vector(b_st_a_en, "b_st_a_en");
#endif

    float a_deg_left = calc_angle_between_vectors_rad(&line_a->vector, &a_st_b_st);
    float a_deg_right = calc_angle_between_vectors_rad(&line_a->vector, &a_st_b_en);
    float b_deg_left = calc_angle_between_vectors_rad(&line_b->vector, &b_st_a_st);
    float b_deg_right = calc_angle_between_vectors_rad(&line_b->vector, &b_st_a_en);
#ifdef DEBUG_VECTOR_CALC
    LOG_DEBUG(VECTOR_MATH, "\n deg %f", a_deg_left);
    LOG_DEBUG(VECTOR_MATH, "\n deg %f", a_deg_right);
    LOG_DEBUG(VECTOR_MATH, "\n deg %f", b_deg_left);
    LOG_DEBUG(VECTOR_MATH, "\n deg %f", b_deg_right);
#endif

    if(is_signe_different(a_deg_left, a_deg_right) && is_signe_different(b_deg_left, b_deg_right)) {
        res = true;
    }

    /*A x + B y + C = 0*/
    return res;
}

char* compose_2d_line_equation_from_line(Line_t line, float* out_equation) {
    Dot_t p1 = line.start;
    Dot_t p2 = get_line_end(line);
    float a = 0.0f, b = 0.0f, c = 0.0f;
#ifdef HAS_LOG
    LOG_DEBUG(VECTOR_MATH, "%s()", __FUNCTION__);
#endif
    static char out_str[100] = "";
    out_equation[0] = 0.0f;
    out_equation[1] = 0.0f;
    out_equation[2] = 0.0f;
    bool done = false;
    bool x_same = is_float_equal_absolute(p2.x, p1.x, 0.01);
    if(false == x_same) {
        a = (1 / (p2.x - p1.x));
    } else {
        done = true;
        out_equation[0] = 1;
        out_equation[2] = p1.x;
        snprintf(out_str, sizeof(out_str), "x=%7.2f", p1.x);
    }
    bool y_same = is_float_equal_absolute(p2.y, p1.y, 0.01);
    if(false == y_same) {
        b = -(1 / (p2.y - p1.y));
    } else {
        done = true;
        out_equation[1] = 1;
        out_equation[2] = p1.y;
        snprintf(out_str, sizeof(out_str), "y=%7.2f", p1.y);
    }
    if((false == x_same) && (false == y_same)) {
        c = (p1.x / (p2.x - p1.x)) - (p1.y / (p2.x - p1.y));
    } else {
        done = true;
        if((true == x_same) && (true == y_same)) {
            snprintf(out_str, sizeof(out_str), "same");
        }
    }

    if(false == done) {
        snprintf(out_str, sizeof(out_str), "%7.2f*x+%7.2f*y=%7.2f", a, b, c);
        out_equation[0] = a;
        out_equation[1] = b;
        out_equation[2] = c;
    }
    return out_str;
}

char* compose_2d_line_equation(Dot_t p1, Dot_t p2, float* out_equation) {
    float a = 0.0f, b = 0.0f, c = 0.0f;
#ifdef HAS_LOG
    LOG_DEBUG(VECTOR_MATH, "%s()", __FUNCTION__);
#endif
    static char out_str[100] = "";
    out_equation[0] = 0.0f;
    out_equation[1] = 0.0f;
    out_equation[2] = 0.0f;
    bool done = false;
    bool x_same = is_float_equal_absolute(p2.x, p1.x, 0.01);
    if(false == x_same) {
        a = (1 / (p2.x - p1.x));
    } else {
        done = true;
        out_equation[0] = 1;
        out_equation[2] = p1.x;
        snprintf(out_str, sizeof(out_str), "x=%7.2f", p1.x);
    }
    bool y_same = is_float_equal_absolute(p2.y, p1.y, 0.01);
    if(false == y_same) {
        b = -(1 / (p2.y - p1.y));
    } else {
        done = true;
        out_equation[1] = 1;
        out_equation[2] = p1.y;
        snprintf(out_str, sizeof(out_str), "y=%7.2f", p1.y);
    }
    if((false == x_same) && (false == y_same)) {
        c = (p1.x / (p2.x - p1.x)) - (p1.y / (p2.x - p1.y));
    } else {
        done = true;
        if((true == x_same) && (true == y_same)) {
            snprintf(out_str, sizeof(out_str), "same");
        }
    }

    if(false == done) {
        snprintf(out_str, sizeof(out_str), "%7.2f*x+%7.2f*y=%7.2f", a, b, c);
        out_equation[0] = a;
        out_equation[1] = b;
        out_equation[2] = c;
    }
    return out_str;
}

static float calc_determinant_2x2(float* arr) {
    float det = 0;
    float a = arr[0];
    float b = arr[1];
    float c = arr[2];
    float d = arr[3];
    det = a * d - b * c;
    return det;
}

static void print_2d_system(float* a, float* b) {
#ifdef HAS_LOG
    LOG_DEBUG(VECTOR_MATH, "%fx + %fy =%f", a[0], a[1], b[0]);
    LOG_DEBUG(VECTOR_MATH, "%fx + %fy =%f\n", a[2], a[3], b[1]);
#endif
}

bool solve_2d_equation(float* a, float* b, float* x_out) {
    float determinamt = calc_determinant_2x2(a);
    float determinamt_x = 0;
    float determinamt_y = 0;
    print_2d_system(a, b);
    bool res = false;
    float* a_temp = (float*)malloc(4 * sizeof(float));
    if(a_temp) {
        memcpy(a_temp, a, 4 * sizeof(float));
        a_temp[0] = b[0];
        a_temp[2] = b[1];
        determinamt_x = calc_determinant_2x2(a_temp);
#ifdef DEBUG_VECTOR_CALC
        LOG_DEBUG(VECTOR_MATH, "determinamt_x %f", determinamt_x);
#endif

        memcpy(a_temp, a, 4 * sizeof(float));
        a_temp[1] = b[0];
        a_temp[3] = b[1];
        determinamt_y = calc_determinant_2x2(a_temp);
#ifdef DEBUG_VECTOR_CALC
        LOG_DEBUG(VECTOR_MATH, "determinamt_y %f", determinamt_y);
#endif
        if(false == is_float_equal_absolute(0.0, determinamt, 0.001)) {
#ifdef DEBUG_VECTOR_CALC
            LOG_DEBUG(VECTOR_MATH, "\n[d] determinamt %f", determinamt);
#endif
            x_out[0] = determinamt_x / determinamt;
            x_out[1] = determinamt_y / determinamt;
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(VECTOR_MATH, "determinamt zero");
#endif
        }
        free(a_temp);
    }
    return res;
}

/*
Calculation of the intersection point of two straight lines. Each line is given
as two points with signed integer coordinates.
*/

bool cacl_intersection_point(Line_t line_a, Line_t line_b, Dot_t* out_intersection_point) {
    bool res = false;
    LOG_DEBUG(VECTOR_MATH, "%s()", __FUNCTION__);

#ifdef HAS_VECTOR_DIAG
    print_line(line_a, "La");
    print_line(line_b, "Lb");
#endif
    res = is_line_segment_crossed(&line_a, &line_b);
    if(res) {
#ifdef HAS_LOG
        LOG_DEBUG(VECTOR_MATH, "intersection exist");
#endif
        float ratio[4];
        float b[2];
        float equation1[3] = {0, 0, 0};
        float equation2[3] = {0, 0, 0};
        char* ex1 = compose_2d_line_equation_from_line(line_a, equation1);
        char* ex2 = compose_2d_line_equation_from_line(line_b, equation2);
#ifdef HAS_LOG
        LOG_DEBUG(VECTOR_MATH, "eq1 %s", ex1);
        LOG_DEBUG(VECTOR_MATH, "eq2 %s", ex2);
#endif
        ratio[0] = equation1[0];
        ratio[1] = equation1[1];
        ratio[2] = equation2[0];
        ratio[3] = equation2[1];
        b[0] = equation1[2];
        b[1] = equation2[2];
        float x_out[2] = {0, 0};
        res = solve_2d_equation(ratio, b, x_out);
        if(res) {
            out_intersection_point->x = x_out[0];
            out_intersection_point->y = x_out[1];
            out_intersection_point->z = 0;
        }
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(VECTOR_MATH, "lack of intersection");
#endif
    }
    return res;
}

float vector_bearings(float d_x, float d_y) {
    float bearing_rad = 0.0;
    VectorF_t direction = {
        .dx = d_x,
        .dy = d_y,
        .dz = 0.0,
    };
    VectorF_t v_axis_x = {
        .dx = 1.0,
        .dy = 0.0,
        .dz = 0.0,
    };
    bearing_rad = calc_angle_between_vectors_rad(&v_axis_x, &direction);
    return bearing_rad;
}

float calc_angle_between_complex_rad(const float complex* const X1, const float complex* const X2) {
    float betta_rad = 0.0;
    float complex_angle_rad = 0.0;
    float x1_arg_rad = carg(*X1);
    float x2_arg_rad = carg(*X2);
    complex_angle_rad = x1_arg_rad - x2_arg_rad;

    VectorF_t v1 = {0};
    VectorF_t v2 = {0};
    v1.dx = creal(*X1);
    v1.dy = cimag(*X1);
    v1.dz = 0.0;

    v2.dx = creal(*X2);
    v2.dy = cimag(*X2);
    v2.dz = 0.0;

    betta_rad = calc_angle_between_vectors_rad(&v1, &v2);
    LOG_DEBUG(VECTOR_MATH, "CompAngle:%fRad,VecAndle:%fRad ", complex_angle_rad, betta_rad);
    return betta_rad;
}

float calc_angle_between_complex_deg(const float complex* const X1, const float complex* const X2) {
    float betta_rad = 0.0;
    float angle_deg = 0.0;
    betta_rad = calc_angle_between_complex_rad(X1, X2);
    angle_deg = rad_2_deg(betta_rad);
    return angle_deg;
}

float calc_angle_between_vectors_atan_rad(const VectorF_t* const a, const VectorF_t* const b) {
    float angle_rad = 0.0;
    if(a) {
        if(b) {
            float abs_a = norm_d(a);
            float abs_b = norm_d(b);
            if(0.0f < abs_a) {
                if(0.0f < abs_b) {
                    LOG_DEBUG(VECTOR_MATH, "V1:%s", VectorToStr(a));
                    LOG_DEBUG(VECTOR_MATH, "V2:%s", VectorToStr(b));
                    float y = (a->dx) * (b->dy) - (a->dy) * (b->dx);
                    float x = (a->dx) * (b->dx) + (a->dy) * (b->dy);
                    angle_rad = atan2(y, x);
                    LOG_DEBUG(VECTOR_MATH, "VecAndle:%fRad ", angle_rad);
                }
            }
        }
    }
    return angle_rad;
}

float calc_angle_between_vectors_atan_deg(const VectorF_t* const v1, const VectorF_t* const v2) {
    float betta_rad = 0.0;
    float angle_deg = 0.0;
    betta_rad = calc_angle_between_vectors_atan_rad(v1, v2);
    angle_deg = rad_2_deg(betta_rad);
    return angle_deg;
}

#if 0
/*
 * I-x
 * q-y
 * */
float calc_fll_discriminator_rad(const VectorF_t* const new, const VectorF_t* const old) {
    float freq_diff_rad = 0.0;
    /* FLL discriminator */
    float f1 = (new->dx == 0) ? (M_PI / 2.0) : atan((float)new->dy / (float)new->dx);
    float f2 = (old->dx == 0) ? (M_PI / 2.0) : atan((float)old->dy / (float)old->dx);
    freq_diff_rad = f1 - f2;

    if(freq_diff_rad > M_PI / 2.0)
        freq_diff_rad = M_PI - freq_diff_rad;

    if(freq_diff_rad < -M_PI / 2.0)
        freq_diff_rad = -M_PI - freq_diff_rad;

    return -freq_diff_rad;
}
#endif

#if 0
float calc_fll_discriminator_deg(const VectorF_t* const v1, const VectorF_t* const v2) {
    float betta_rad = 0.0f;
    float angle_deg = 0.0f;
    betta_rad = calc_fll_discriminator_rad(v1, v2);
    angle_deg = rad_2_deg(betta_rad);
    return angle_deg;
}
#endif

/*
 proofs that :225 deg is the same as -135 deg
 */
bool math_is_equal_angles_deg(const float angle1_deg, const float angle2_deg, const float error_deg) {
    bool res = false;
    LOG_DEBUG(VECTOR_MATH, "Are %f deg and %f deg equal?", angle1_deg, angle2_deg);
    VectorF_t v1;
    v1.dx = cosf(DEG_2_RAD(angle1_deg));
    v1.dy = sinf(DEG_2_RAD(angle1_deg));
    v1.dz = 0.0f;

    VectorF_t v2;
    v2.dx = cosf(DEG_2_RAD(angle2_deg));
    v2.dy = sinf(DEG_2_RAD(angle2_deg));
    v2.dz = 0.0f;

    float angle_error_deg = calc_angle_between_vectors_deg(&v1, &v2);
    if(fabsf(angle_error_deg) < error_deg) {
        res = true;
    }
    return res;
}
