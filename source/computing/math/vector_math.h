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


float norm_f(const VectorF_t* const Node);
double norm_d(const Vector_t* const Node);

float calc_angle_between_3d_f_vectors_rad(const VectorF_t* const v1, const  VectorF_t*  const v2);

double calc_angle_between_complex_deg(const double complex* const X1,
        const double complex* const X2 );
double calc_angle_between_complex_rad(const double complex* const X1,
        const double complex* const X2 );


Dot_t get_line_end(Line_t in_line);
float radians2deg_f(float radians);
double radians2deg(double radians);
bool cacl_intersection_point(Line_t line1, Line_t line2, Dot_t* out_intersection_point);
bool is_line_segment_crossed(Line_t* line_a, Line_t* line_b);

double vector_bearings( double d_x, double d_y);
double calc_angle_between_vectors_rad(const Vector_t* const v1, const  Vector_t*  const v2);
double calc_angle_between_vectors_deg(const Vector_t* const v1, const  Vector_t*  const v2);
double calc_angle_between_vectors_naiv_deg(const Vector_t* const v1, const  Vector_t*  const v2);
double calc_angle_between_vectors_atan_deg(const Vector_t* const v1, const  Vector_t*  const v2);
double calc_angle_between_vectors_atan_rad(const Vector_t* const a, const  Vector_t*  const b);

double calc_angle_between_vectors_naiv_rad(
        const Vector_t* const v1,
        const  Vector_t* const v2);
Vector_t init_vector(double dx, double dy, double dz);
Dot_t init_dot(double x, double y, double z);
char* compose_2d_line_equation(Dot_t p1, Dot_t p2, double* out_equation);
char* compose_2d_line_equation_from_line(Line_t line, double* out_equation);
bool solve_2d_equation(double* a, double* b, double* x_out);

double calc_fll_discriminator_rad( const Vector_t* const new, const  Vector_t*  const old);
double calc_fll_discriminator_deg( const Vector_t* const new, const  Vector_t*  const old);

#ifdef __cplusplus
}
#endif

#endif /*VECTOR_MATH_H*/
