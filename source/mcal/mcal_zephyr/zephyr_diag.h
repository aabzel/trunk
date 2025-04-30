#ifndef ZEPHYR_DIAG_H
#define ZEPHYR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

const char* ErrNo2Str(int err_no);


#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DIAG_H */
