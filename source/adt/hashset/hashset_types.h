#ifndef HASHSET_TYPEES_H
#define HASHSET_TYPEES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#ifndef HAS_HASHSET
#error "+HAS_HASHSET"
#endif

#ifndef HAS_ADT
#error "+HAS_ADT"
#endif

#ifndef HAS_CRC32
#error "+HAS_CRC32"
#endif

#ifndef HAS_CRC
#error "+HAS_CRC"
#endif

typedef struct {
    uint32_t crc32;
    uint32_t cnt;
} HashSetEntry_t;

typedef struct {
    uint32_t err_cnt;
    uint32_t size;
    uint32_t cnt;
    HashSetEntry_t* heap;
    bool init_done;
} HashSet_t;

#ifdef __cplusplus
}
#endif

#endif /* HASHSET_TYPEES_H */
