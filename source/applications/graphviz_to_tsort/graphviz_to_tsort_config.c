#include "graphviz_to_tsort_config.h"

#include "graphviz_to_tsort_types.h"
#include "data_utils.h"

const GraphvizToTsortConfig_t GraphvizToTsortConfig = {
        .gv_filename = "dep.gv",
        .tsort_file = "tsort_generated.txt",
        .valid = true,
};

GraphvizToTsortHandle_t GraphvizToTsortInstance = {
    .valid = true,
};

