#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "std_includes.h"
#include "vector_types.h"
#include "vector_diag.h"

//#define ACOS_ARG_ERROR  0.00000001f
#define ACOS_ARG_ERROR  0.00001f

float norm_f(const VectorF_t* const Node);
float deg2radians(float degrees) ;
float norm_d(const VectorF_t* const Node);

float calc_angle_between_3d_f_vectors_rad(const VectorF_t* const v1, const  VectorF_t*  const v2);

float calc_angle_between_complex_deg(const float complex* const X1,
        const float complex* const X2 );
float calc_angle_between_complex_rad(const float complex* const X1,
        const float complex* const X2 );


Dot_t get_line_end(Line_t in_line);
float radians2deg_f(float radians);
float radians2deg(float radians);
bool cacl_intersection_point(Line_t line1, Line_t line2, Dot_t* out_intersection_point);
bool is_line_segment_crossed(Line_t* line_a, Line_t* line_b);

float vector_bearings( float d_x, float d_y);
float calc_angle_between_vectors_rad(const VectorF_t* const v1, const  VectorF_t*  const v2);
float calc_angle_between_vectors_deg(const VectorF_t* const v1, const  VectorF_t*  const v2);
float calc_angle_between_vectors_naiv_deg(const VectorF_t* const v1, const  VectorF_t*  const v2);
float calc_angle_between_vectors_atan_deg(const VectorF_t* const v1, const  VectorF_t*  const v2);
float calc_angle_between_vectors_atan_rad(const VectorF_t* const a, const  VectorF_t*  const b);

float calc_angle_between_vectors_naiv_rad( const VectorF_t* const v1,
                                           const  VectorF_t* const v2);
VectorF_t init_vector(float dx, float dy, float dz);
Dot_t init_dot(float x, float y, float z);
char* compose_2d_line_equation(Dot_t p1, Dot_t p2, float* out_equation);
char* compose_2d_line_equation_from_line(Line_t line, float* out_equation);
bool solve_2d_equation(float* a, float* b, float* x_out);

bool math_is_equal_angles_deg(const float angle1_deg,
                              const float angle2_deg,
                              const float error_deg);

float calc_fll_discriminator_rad( const VectorF_t* const new, const  VectorF_t*  const old);
float calc_fll_discriminator_deg( const VectorF_t* const new, const  VectorF_t*  const old);

#ifdef __cplusplus
}
#endif

#endif /*VECTOR_MATH_H*/
