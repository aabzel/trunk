#ifndef GFSK_DIAG_H
#define GFSK_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gfsk_constants.h"

typedef struct xBandWithVal_t {
    GfskBandwidth_t code;
    uint32_t bandwith_hz;
} BandWithVal_t;

char* PreDetLenToStr(uint8_t code);
char* SyncWordToStr(uint64_t syn_word);
char* CrcToStr(uint8_t code);
char* GfskBandwithToStr(uint8_t code);
char* GfskPacetTypeToStr(uint8_t code);
char* PulseShapeToStr(uint8_t code);
char* SyncWordLenToStr(uint8_t bits_cnt);
uint32_t GfskBandWith2Hz(uint8_t code);

#ifdef __cplusplus
}
#endif

#endif /* GFSK_DIAG_H */
