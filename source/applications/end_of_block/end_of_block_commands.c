#include "end_of_block_commands.h"


#include "end_of_block.h"
#include "end_of_block_diag.h"
#include "cli_diag.h"
#include "convert.h"
#include "log.h"


bool end_of_block_check_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t lines = 5;

    char c_file_name[500]={0};
    cli_argument_diag(argc, argv);

    if ( 1<= argc) {
        res = try_str2uint32(argv[0], &lines);
    }

    if ( 2<= argc) {
        strcpy(c_file_name, argv[1]);
        res = true;
    }

    if(res) {
        res = end_of_block_check(c_file_name, lines);
        log_res(  END_OF_BLOCK  , res, "Check,EndOfBlock");
    } else {
        LOG_ERROR(END_OF_BLOCK, "Usage: eob Treshold file");
    }
    return res;
}




