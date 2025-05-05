#include "code_style_checker.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "file_pc.h"
#include "csv.h"
#include "win_utils.h"
#include "str_utils_ex.h"


bool code_style_checker_mcal_init(void) {
    bool res = true;
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    log_level_get_set(CODE_STYLE_CHECKER, LOG_LEVEL_INFO);
    LOG_INFO(CODE_STYLE_CHECKER, "CODE_STYLE_CHECKER_VERSION:%u", CODE_STYLE_CHECKER_DRIVER_VERSION);
    return res;
}


static bool generate_static_func_definition_list(const char *const file_name_c,  char *const out) {
    bool res = false;
    if (file_name_c) {
        LOG_INFO(CODE_STYLE_CHECKER, "Gen,Static,Fun,Def,List,*.c:[%s]", file_name_c);
        char cTagsRepFileName[500] = { 0 };
        strcpy(cTagsRepFileName, "");

        static char FunctionListDefine[500] = { 0 };
        char cTagsFilePath[500] = { 0 };
        uint32_t cnt = csv_cnt(file_name_c, '.');
        LOG_DEBUG(CODE_STYLE_CHECKER, "DotCnt:%u", cnt);
        res = csv_parse_text(file_name_c, '.', cnt-2, cTagsFilePath, sizeof(cTagsFilePath));
        if (res) {
            LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsFilePathFor:[%s]", cTagsFilePath);
            cnt = csv_cnt(cTagsFilePath, '/');
            if (cnt) {
                LOG_DEBUG(CODE_STYLE_CHECKER, "FolderCnt:%u", cnt);
                res = csv_parse_text(cTagsFilePath, '/', cnt - 1, cTagsRepFileName,
                        sizeof(cTagsRepFileName));
                if (res) {
                    LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsRepFileName:[%s]", cTagsRepFileName);
                    snprintf(FunctionListDefine, sizeof(FunctionListDefine), "%s_function_definition.txt",
                            cTagsRepFileName);

                    snprintf(cTagsRepFileName, sizeof(cTagsRepFileName), "%s.txt",
                            cTagsRepFileName);

                } else {
                    LOG_ERROR(CODE_STYLE_CHECKER, "get,fileName,Err");
                }
            }
        } else {
            LOG_ERROR(CODE_STYLE_CHECKER, "get,path,Err");
        }
        char CmdCommand[500] = { 0 };

        file_pc_delete(cTagsRepFileName) ;

        char cTagsOptions[500] = { 0 };
        strcpy(cTagsOptions, "");
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s--sort=no", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s --kinds-c=f", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s -f%s", cTagsOptions, cTagsRepFileName);
        LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsOptions:[%s]", cTagsOptions);

        strcpy(CmdCommand, "");
        snprintf(CmdCommand, sizeof(CmdCommand), "ctags.exe %s %s", cTagsOptions, file_name_c);
        LOG_DEBUG(CODE_STYLE_CHECKER, "TryExeCmd:[%s]", CmdCommand);
        res = win_cmd_run(CmdCommand);
        if(res){
            strcpy(CmdCommand, "");
            snprintf(CmdCommand, sizeof(CmdCommand), "sed -i '/!/d' %s", cTagsRepFileName);
            res = win_cmd_run(CmdCommand);

            strcpy(CmdCommand, "");
            snprintf(CmdCommand, sizeof(CmdCommand), "sed -i '/static /!d' %s", cTagsRepFileName);
            res = win_cmd_run(CmdCommand);

            strcpy(CmdCommand, "");
            snprintf(CmdCommand, sizeof(CmdCommand), "gawk '{print $1}' %s > %s", cTagsRepFileName,
                    FunctionListDefine);
            res = win_cmd_run(CmdCommand);
            if(out) {
                strcpy(out,FunctionListDefine);
            }
            file_pc_delete(cTagsRepFileName);
        }
    }
    return res;
}

static bool generate_static_func_declare_list(const char *const file_name_c,  char *const out) {
    bool res = false;
    if (file_name_c) {
        LOG_INFO(CODE_STYLE_CHECKER, "Gen,Static,Fun,Declare,List,*.c:[%s]", file_name_c);
        char cTagsRepFileName[500] = { 0 };
        strcpy(cTagsRepFileName, "");

        static char FunctionListDeclareFile[500] = { 0 };
        char cTagsFilePathForH[500] = { 0 };
        uint32_t cnt = csv_cnt(file_name_c, '.');
        LOG_DEBUG(CODE_STYLE_CHECKER, "DotCnt:%u", cnt);
        res = csv_parse_text(file_name_c, '.', cnt-2, cTagsFilePathForH, sizeof(cTagsFilePathForH));
        if (res) {
            LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsFilePathForH:[%s]", cTagsFilePathForH);
            cnt = csv_cnt(cTagsFilePathForH, '/');
            if (cnt) {
                LOG_DEBUG(CODE_STYLE_CHECKER, "FolderCnt:%u", cnt);
                res = csv_parse_text(cTagsFilePathForH, '/', cnt - 1, cTagsRepFileName,
                        sizeof(cTagsRepFileName));
                if (res) {
                    LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsRepFileName:[%s]", cTagsRepFileName);
                    snprintf(FunctionListDeclareFile, sizeof(FunctionListDeclareFile), "%s_function_declarations.txt",
                            cTagsRepFileName);

                    snprintf(cTagsRepFileName, sizeof(cTagsRepFileName), "%s.txt",
                            cTagsRepFileName);

                } else {
                    LOG_ERROR(CODE_STYLE_CHECKER, "get,fileName,Err");
                }
            }
        } else {
            LOG_ERROR(CODE_STYLE_CHECKER, "get,path,Err");
        }
        char CmdCommand[500] = { 0 };

        file_pc_delete(cTagsRepFileName) ;

        char cTagsOptions[500] = { 0 };
        strcpy(cTagsOptions, "");
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s --sort=no", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s --kinds-c=p", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s -f%s", cTagsOptions, cTagsRepFileName);
        LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsOptions:[%s]", cTagsOptions);

        strcpy(CmdCommand, "");
        snprintf(CmdCommand, sizeof(CmdCommand), "ctags.exe %s %s", cTagsOptions, file_name_c);
        LOG_DEBUG(CODE_STYLE_CHECKER, "TryExeCmd:[%s]", CmdCommand);
        res = win_cmd_run(CmdCommand);
        if(res){
            strcpy(CmdCommand, "");
            snprintf(CmdCommand, sizeof(CmdCommand), "sed -i '/!/d' %s", cTagsRepFileName);
            res = win_cmd_run(CmdCommand);

            strcpy(CmdCommand, "");
            snprintf(CmdCommand, sizeof(CmdCommand), "gawk '{print $1}' %s > %s",
                     cTagsRepFileName,
                     FunctionListDeclareFile);
            res = win_cmd_run(CmdCommand);
            if(out){
                strcpy(out, FunctionListDeclareFile);
            }
            file_pc_delete(cTagsRepFileName) ;
        }

    }
    return res;
}


/*[REQ_CODE_0412] The order of function declarations must match the order of function definitions*/

bool code_style_checker_generate_h_func_list(const char *const file_name_h,  char *const out) {
    bool res = false;
    if (file_name_h) {
        LOG_INFO(CODE_STYLE_CHECKER, "Gen,H,fun,List,File,Name*.h:[%s]", file_name_h);
        char cTagsFileNameForH[500] = { 0 };
        strcpy(cTagsFileNameForH, "");

        static char FunctionListH[500] = { 0 };
        char cTagsFilePathForH[500] = { 0 };
        uint32_t cnt = csv_cnt(file_name_h, '.');
        LOG_DEBUG(CODE_STYLE_CHECKER, "DotCnt:%u", cnt);
        res = csv_parse_text(file_name_h, '.', cnt-2, cTagsFilePathForH, sizeof(cTagsFilePathForH));
        if (res) {
            LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsFilePathForH:[%s]", cTagsFilePathForH);
            cnt = csv_cnt(cTagsFilePathForH, '/');
            if (cnt) {
                LOG_DEBUG(CODE_STYLE_CHECKER, "FolderCnt:%u", cnt);
                res = csv_parse_text(cTagsFilePathForH, '/', cnt - 1, cTagsFileNameForH,
                        sizeof(cTagsFileNameForH));
                if (res) {
                    LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsFileNameForH:[%s]", cTagsFileNameForH);
                    snprintf(FunctionListH, sizeof(FunctionListH), "%s_h_functions.txt",
                            cTagsFileNameForH);

                    snprintf(cTagsFileNameForH, sizeof(cTagsFileNameForH), "%s.txt",
                            cTagsFileNameForH);

                } else {
                    LOG_ERROR(CODE_STYLE_CHECKER, "get,fileName,Err");
                }
            }
        } else {
            LOG_ERROR(CODE_STYLE_CHECKER, "get,path,Err");
        }
        char CmdCommand[500] = { 0 };

        file_pc_delete(cTagsFileNameForH) ;

        char cTagsOptions[500] = { 0 };
        strcpy(cTagsOptions, "");
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s --sort=no", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s --kinds-c=fp", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s -f%s", cTagsOptions, cTagsFileNameForH);
        LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsOptions:[%s]", cTagsOptions);

        strcpy(CmdCommand, "");
        snprintf(CmdCommand, sizeof(CmdCommand), "ctags.exe %s %s", cTagsOptions, file_name_h);
        LOG_DEBUG(CODE_STYLE_CHECKER, "TryExeCmd:[%s]", CmdCommand);
        res = win_cmd_run(CmdCommand);


        strcpy(CmdCommand, "");
        snprintf(CmdCommand, sizeof(CmdCommand), "sed -i '/!/d' %s", cTagsFileNameForH);
        res = win_cmd_run(CmdCommand);

        strcpy(CmdCommand, "");
        snprintf(CmdCommand, sizeof(CmdCommand), "gawk '{print $1}' %s > %s", cTagsFileNameForH,
                FunctionListH);
        res = win_cmd_run(CmdCommand);
        if(out){
            strcpy(out,FunctionListH);
        }
        file_pc_delete(cTagsFileNameForH) ;

    }
    return res;
}

bool code_style_checker_generate_c_func_list(const char *const file_name_c, char * const out){
    bool res = false;
    if (file_name_c) {
        //log_level_get_set(PC, LOG_LEVEL_DEBUG);
        LOG_INFO(CODE_STYLE_CHECKER, "Gen,*.C,fun,list,file_name_c:[%s]", file_name_c);

        char cTagsFileNameForC[500] = { 0 };
        char FunctionListC[500] = { 0 };
        char cTagsFilePathForC[500] = { 0 };
        strcpy(cTagsFilePathForC, "");
        uint32_t cnt = csv_cnt(file_name_c, '.');
        LOG_DEBUG(CODE_STYLE_CHECKER, "Csv,Dot,Sep,Cnt:%u", cnt);
        res = csv_parse_text(file_name_c, '.', cnt-2, cTagsFilePathForC, sizeof(cTagsFilePathForC));
        if (res) {
            LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsFilePathForC:[%s]", cTagsFilePathForC);
            cnt = csv_cnt(cTagsFilePathForC, '/');
            if (cnt) {
                LOG_DEBUG(CODE_STYLE_CHECKER, "FolderCnt:%u", cnt);
                res = csv_parse_text(cTagsFilePathForC, '/', cnt - 1, cTagsFileNameForC,
                        sizeof(cTagsFileNameForC));
                if (res) {
                    LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsFileNameForC:[%s]", cTagsFileNameForC);
                    snprintf(FunctionListC, sizeof(FunctionListC), "%s_c_functions.txt",
                            cTagsFileNameForC);
                    snprintf(cTagsFileNameForC, sizeof(cTagsFileNameForC), "%s.txt",
                            cTagsFileNameForC);

                } else {
                    LOG_ERROR(CODE_STYLE_CHECKER, "get,fileName,Err");
                }
            }
        } else {
            LOG_ERROR(CODE_STYLE_CHECKER, "get,path,Err");
        }
        char CmdCommand[500] = { 0 };
        char cTagsOptions[500] = { 0 };
        strcpy(cTagsOptions, "");

        file_pc_delete(cTagsFileNameForC) ;


        LOG_DEBUG(CODE_STYLE_CHECKER, "file_name_c:[%s]", file_name_c);

        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s--sort=no", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s -x --c-types=f", cTagsOptions);
        snprintf(cTagsOptions, sizeof(cTagsOptions), "%s -f%s", cTagsOptions, cTagsFileNameForC);
        LOG_DEBUG(CODE_STYLE_CHECKER, "cTagsOptions:[%s]", cTagsOptions);

        strcpy(CmdCommand, "");
        snprintf(CmdCommand, sizeof(CmdCommand), "ctags.exe %s %s", cTagsOptions, file_name_c);
        LOG_DEBUG(CODE_STYLE_CHECKER, "TryExeCmd:[%s]", CmdCommand);
        res = win_cmd_run(CmdCommand);
        if(res) {
            strcpy(CmdCommand, "");
            snprintf(CmdCommand, sizeof(CmdCommand), "sed -i '/static/d' %s", cTagsFileNameForC);
            res = win_cmd_run(CmdCommand);
            if(res) {
                strcpy(CmdCommand, "");
                snprintf(CmdCommand, sizeof(CmdCommand), "gawk '{print $1}' %s > %s", cTagsFileNameForC,
                        FunctionListC);
                res = win_cmd_run(CmdCommand);

                if(out) {
                    strcpy(out,FunctionListC);
                }
                file_pc_delete(cTagsFileNameForC) ;
            }
        }

    }
    return res;
}

bool code_style_checker_static_proto(const char *const file_name_c){
    bool res = false;
    if (file_name_c) {
        LOG_INFO(CODE_STYLE_CHECKER, "Check,Static,Prototype,Order:[%s]", file_name_c);
        char CmdCommand[500] = { 0 };
        char StaticFunDecListFile[500] = { 0 };
        char StaticFunDefListFile[500] = { 0 };

        res = generate_static_func_definition_list(file_name_c, StaticFunDefListFile);
        if(res) {
            res = generate_static_func_declare_list(file_name_c, StaticFunDecListFile);
            if(res) {
                strcpy(CmdCommand, "");
                snprintf(CmdCommand, sizeof(CmdCommand), "cmp -s %s %s", StaticFunDecListFile, StaticFunDefListFile);
                res = win_cmd_run(CmdCommand);
                if (res) {
                    LOG_INFO(CODE_STYLE_CHECKER, "Prototype,Order,Ok");
                    file_pc_delete(StaticFunDecListFile);
                    file_pc_delete(StaticFunDefListFile);
                } else {
                    LOG_ERROR(CODE_STYLE_CHECKER, "Static,Prototype,Order,Err");
                    LOG_ERROR(CODE_STYLE_CHECKER, "%s",StaticFunDecListFile);
                    LOG_ERROR(CODE_STYLE_CHECKER, "%s",StaticFunDefListFile);
                    LOG_ERROR(CODE_STYLE_CHECKER, "%s",file_name_c);
                }
            }
        }

    }
    return res;
}

bool code_style_checker_global_proto(const char *const file_name_c, const char *const h_file_name) {
    bool res = false;
    if (file_name_c) {
        //log_level_get_set(PC, LOG_LEVEL_DEBUG);
        LOG_INFO(CODE_STYLE_CHECKER, "Check,Global,Prototype,Order:[%s]", file_name_c);
        char CmdCommand[500] = { 0 };
        char FunctionListH[500] = { 0 };
        char FunctionListC[500] = { 0 };
        char file_name_h[500] = { 0 };

        if(h_file_name) {
             strcpy(file_name_h,h_file_name);
        }else {
            strcpy(file_name_h,file_name_c);
            res = replace_substring(file_name_h, ".c", ".h") ;
            LOG_INFO(CODE_STYLE_CHECKER, "Guessed *.h:[%s]", file_name_h);
        }

#if 0
        char cTagsFilePathForC[500] = { 0 };
        strcpy(cTagsFilePathForC, "");
        uint32_t cnt =  csv_cnt(file_name_c,'.');
        LOG_INFO(CODE_STYLE_CHECKER, "DotSepElementsCnt:[%u]", cnt);
        res = csv_parse_text(file_name_c, '.', cnt-2, cTagsFilePathForC, sizeof(cTagsFilePathForC));
        if (res) {
            LOG_INFO(CODE_STYLE_CHECKER, "cTagsFilePathForC:[%s]", cTagsFilePathForC);
            snprintf(file_name_h, sizeof(file_name_h), "%s.h", cTagsFilePathForC);
        } else {
            LOG_ERROR(CODE_STYLE_CHECKER, "get,path,Err");
        }
#endif

        res = code_style_checker_generate_h_func_list(file_name_h, FunctionListH);
        if(res) {
            res = code_style_checker_generate_c_func_list(file_name_c, FunctionListC);
            if(res) {
                strcpy(CmdCommand, "");
                snprintf(CmdCommand, sizeof(CmdCommand), "cmp -s %s %s", FunctionListH, FunctionListC);
                res = win_cmd_run(CmdCommand);
                if (res) {
                    LOG_INFO(CODE_STYLE_CHECKER, "Prototype,Order,Ok");
                    file_pc_delete(FunctionListH) ;
                    file_pc_delete(FunctionListC) ;
                } else {
                    LOG_ERROR(CODE_STYLE_CHECKER, "Prototype,Order,Err",FunctionListH, FunctionListC);
                     LOG_ERROR(CODE_STYLE_CHECKER, "%s",file_name_h);
                     LOG_ERROR(CODE_STYLE_CHECKER, "%s",file_name_c);
                }
            }
        }

    }
    return res;
}

bool code_style_checker_proto(const char* const file_name_relative_c,
                              const char *const file_name_h){
    bool res = false;
    if(file_name_relative_c) {
        char file_name_abs_c[300]={0};
        res = file_pc_realpath(file_name_relative_c, file_name_abs_c);
        if(res) {
            LOG_INFO(CODE_STYLE_CHECKER, "Check,All,Prototype,Order:[%s]", file_name_abs_c);
            res = code_style_checker_static_proto(file_name_abs_c);
            if (file_name_h) {
                LOG_INFO(CODE_STYLE_CHECKER, "Special,*.H:[%s]", file_name_h);
                res = code_style_checker_global_proto(file_name_abs_c, file_name_h);
            } else {
                res = code_style_checker_global_proto(file_name_abs_c, NULL);
            }
        }
    }

    return res;
}

