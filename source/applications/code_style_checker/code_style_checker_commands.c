#include "code_style_checker_commands.h"


#include "code_style_checker.h"
#include "code_style_checker_diag.h"
#include "cli_diag.h"
#include "convert.h"
#include "log.h"


bool code_style_checker_static_proto_command(int32_t argc, char* argv[]){
    bool res = false;
    char c_file_name[500]={0};
    cli_argument_diag(argc, argv);

    if ( 1<= argc) {
        strcpy(c_file_name, argv[0]);
        res = true;
    }

    if(res) {
        res = code_style_checker_static_proto(c_file_name);
        log_res(  CODE_STYLE_CHECKER  , res, "Check,Static,Proto");
    } else {
        LOG_ERROR(CODE_STYLE_CHECKER, "Usage: csp");
    }
    return res;
}

/*
  ll CodeStyle debug ; csp dddddd.c
  ll CodeStyle debug ;cpr cccc.c
*/
bool code_style_checker_proto_command(int32_t argc, char* argv[]){
    bool res = false;
    char c_file_name[500]={0};
    char h_file_name[500]={0};

    cli_argument_diag(argc, argv);

    if(1<= argc) {
        strcpy(c_file_name, argv[0]);
        res = true;
    }

    if(2<= argc) {
        strcpy(h_file_name, argv[1]);
        res = true;
    }


    if(res) {
        switch(argc) {
            case 1: {
                res = code_style_checker_proto(c_file_name,NULL);
                log_res(  CODE_STYLE_CHECKER  , res, "Check,Proto,C");
            } break;
            case 2:{
                res = code_style_checker_proto(c_file_name,h_file_name);
                log_res(  CODE_STYLE_CHECKER  , res, "Check,Proto,CH");
            } break;
            default: break;
        }

        log_res(CODE_STYLE_CHECKER, res, "");
    } else {
        LOG_ERROR(CODE_STYLE_CHECKER, "Usage: cpr");
    }
    return res;
}

bool code_style_checker_global_proto_command(int32_t argc, char* argv[]){
    bool res = false;
    char c_file_name[500]={0};
    char h_file_name[500]={0};

    cli_argument_diag(argc, argv);

    if(1<= argc) {
        strcpy(c_file_name, argv[0]);
        res = true;
    }

    if(2<= argc) {
        strcpy(h_file_name, argv[1]);
        res = true;
    }


    if(res) {
        switch(argc) {
            case 1: {
                res = code_style_checker_global_proto(c_file_name,NULL);
                log_res(  CODE_STYLE_CHECKER  , res, "Check,Proto,C");
            } break;
            case 2:{
                res = code_style_checker_global_proto(c_file_name,h_file_name);
                log_res(  CODE_STYLE_CHECKER  , res, "Check,Proto,CH");
            } break;
            default: break;
        }

        log_res(CODE_STYLE_CHECKER, res, "");
    } else {
        LOG_ERROR(CODE_STYLE_CHECKER, "Usage: cgp");
    }
    return res;
}



