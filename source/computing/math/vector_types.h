#ifndef VECTOR_TYPES_H
#define VECTOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef M_PI
#define M_PI 3.14159
#endif

#define EPSILONT  (0.00000000001)

#define M_2_PI (6.28318)

typedef struct  {
    double x;
    double y;
    double z;
} Dot_t;

typedef struct  {
    double dx;
    double dy;
    double dz;
} Vector_t;

typedef struct  {
    float dx;
    float dy;
    float dz;
} VectorF_t;



typedef struct  {
    Dot_t start;
    Vector_t vector;
} Line_t;


#ifdef __cplusplus
}
#endif

#endif /*VECTOR_TYPES_H*/
