#ifndef FFT_DEP_H
#define FFT_DEP_H


#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MATH
#error "+HAS_MATH"
#endif

#ifndef HAS_FFT
#error "+HAS_FFT"
#endif

#ifndef HAS_COMPLEX
#error "+HAS_COMPLEX"
#endif

#ifdef __cplusplus
}
#endif

#endif /* FFT_DEP_H */
