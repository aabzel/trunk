#ifndef TOPO_SORT_TOPO_SORT_TYPES_H
#define TOPO_SORT_TOPO_SORT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "topo_sort_const.h"

#define RES_SIZE 5000
#define ONE_DEP_SIZE 1000
#define MAX_DEP_LIST 200

typedef struct  {
    char name[ONE_DEP_SIZE];
    bool valid;
    uint32_t size;
    uint32_t child_cnt;
}DepNode_t;



struct sGraphNode_t {
    char name[100];
    bool visited;
    bool valid;
    uint32_t child_cnt;
    struct sGraphNode_t* Child[20];
};

typedef struct sGraphNode_t GraphNode_t;

#define TOPO_SORT_COMMON_VARIABLES          \
    uint8_t num;                          \
    char* name;                           \
    bool valid;

typedef struct {
    TOPO_SORT_COMMON_VARIABLES
	DepNode_t DepArray[MAX_DEP_LIST];
    char result[RES_SIZE];
    char result2[RES_SIZE];
}TopoSortHandle_t;

typedef struct {
    TOPO_SORT_COMMON_VARIABLES
}TopoSortConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* TOPO_SORT_TOPO_SORT_TYPES_H */
