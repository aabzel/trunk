#ifndef UBX_DIAG_H
#define UBX_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct xNavId2strLut_t{
    uint8_t id;
    char *name;
}NavId2StrLut_t;

char* ClassId2str(uint8_t cls, uint8_t id);
char* FixType2Str(uint8_t mode);
char* ReceiverMode2Str(uint8_t mode);
char* class2str(uint8_t class_id);
bool ubx_print_frame(uint8_t* frame);

#ifdef __cplusplus
}
#endif

#endif /* UBX_DIAG_H */
