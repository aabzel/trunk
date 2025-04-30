#ifndef DSP_CONST_H
#define DSP_CONST_H

typedef enum {
    SAMPLE_MODE_MONO = 1,
    SAMPLE_MODE_STEREO = 2,

    SAMPLE_MODE_UNDEF = 0,
} SampleMode_t;


typedef enum {
    DSP_FILTER_TYPE_FIR= 1,
    DSP_FILTER_TYPE_IIR= 2,
    DSP_FILTER_TYPE_UNDEF = 0,
} DspFilterType_t;

#endif /* DSP_CONST_H */


