#include "topo_sort_commands.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "convert.h"
#include "topo_sort.h"
#include "log.h"

//psd 1
bool topo_sort_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;


    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(TOPO_SORT, "Arg1 FreqErr %s", argv[0]);
        }
    }


    if(res) {
        res = topo_sort_diag(num);
        if(res) {
        } else {
            LOG_ERROR(TOPO_SORT, "GenerateErr");
        }
    } else {
        LOG_ERROR(TOPO_SORT, "Usage: psd Num");
    }
    return res;
}

/*
 * psn 1 1
 * psn 1 2
 * psn 1 3
 * psn 1 4
 */
bool topo_sort_run_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char csv_file[80] = {0};
    char csv_dep_list[80] = {0};
    LOG_INFO(TOPO_SORT, "argc:%u", argc);
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = strcpy(csv_file,argv[1]);
    }

    if(3 <= argc) {
        res = strcpy(csv_dep_list,argv[2]);
    }

    if(res) {
        LOG_INFO(TOPO_SORT, "CsvFile:[%s][%s]", csv_file,csv_dep_list);
        res = topo_sort_run(num,csv_file,csv_dep_list);
        if(res) {
        	LOG_INFO(TOPO_SORT, "ProcOk");
        } else {
            LOG_ERROR(TOPO_SORT, "ProcErr");
        }
    }

    return res;
}
