#ifndef MODULATOR_CONST_H
#define MODULATOR_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MODULATION_FSK = 1,
    MODULATION_BPSK = 2,
    MODULATION_OOK = 3,

    MODULATION_UNDEF = 0,
}Modulation_t;

#ifdef __cplusplus
}
#endif

#endif /* MODULATOR_CONST_H */
