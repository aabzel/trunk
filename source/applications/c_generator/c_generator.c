#include "c_generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "file_pc.h"
#include "log.h"
#include "str_utils_ex.h"
#include "win_utils.h"

// REQ_CODE_0503
bool c_generator_eof(void) {
    bool res = true;
    cli_printf("//******************************** end of file ********************************" CRLF);
    return res;
}

bool c_generator_function_cap(char* const function_name) {
    bool res = false;
    if(function_name) {
        cli_printf("//*****************************************************************************" CRLF);
        cli_printf("// @Function      %s" CRLF, function_name);
        cli_printf("//-----------------------------------------------------------------------------" CRLF);
        cli_printf("// @Description   %s() function" CRLF, function_name);
        cli_printf("//-----------------------------------------------------------------------------" CRLF);
        cli_printf("// @Notes" CRLF);
        cli_printf("//-----------------------------------------------------------------------------" CRLF);
        cli_printf("// @ReturnValue" CRLF);
        cli_printf("//-----------------------------------------------------------------------------" CRLF);
        cli_printf("// @Parameters" CRLF);
        cli_printf("//*****************************************************************************" CRLF);
        cli_printf("// end of %s()" CRLF, function_name);
        res = true;
    }
    return res;
}

// end of TEST_MODULE_SecondFunc()

bool c_generator_mcal_init(void) {
    bool res = true;
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    log_level_get_set(C_GENERATOR, LOG_LEVEL_INFO);
    LOG_INFO(C_GENERATOR, "C_GENERATOR_VERSION:%u", C_GENERATOR_DRIVER_VERSION);
    return res;
}

bool c_generator_proc(void) {
    bool res = false;
    return res;
}

FuncNameParseInput_t fund_func_classify_letter(char letter) {
    FuncNameParseInput_t input = FUN_NAME_PARSE_INPUT_UNDEF;
    switch(letter) {
    case ' ':
        input = FUN_NAME_PARSE_INPUT_SPACE;
        break;
    case '*':
        input = FUN_NAME_PARSE_INPUT_STAR;
        break;
    case '(':
        input = FUN_NAME_PARSE_INPUT_OPENING_PARENTHESIS;
        break;
    case ')':
        input = FUN_NAME_PARSE_INPUT_CLOSING_PARENTHESIS;
        break;
    case ';':
        input = FUN_NAME_PARSE_INPUT_SEMICOLON;
        break;
    case '\n':
        input = FUN_NAME_PARSE_INPUT_NEW_LINE;
        break;
    case '\r':
        input = FUN_NAME_PARSE_INPUT_CARRIAGE_RETURN;
        break;
    case '{':
        input = FUN_NAME_PARSE_INPUT_OPENING_BRACE;
        break;
    case '}':
        input = FUN_NAME_PARSE_INPUT_CLOSING_BRACE;
        break;

    default:
        break;
    }
    return input;
}

bool parse_func_name_proc_idle(cGeneratorHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case FUN_NAME_PARSE_INPUT_SPACE: {
        res = true;
    } break;
    case FUN_NAME_PARSE_INPUT_LETTER: {
    } break;
    case FUN_NAME_PARSE_INPUT_STAR: {
    } break;
    case FUN_NAME_PARSE_INPUT_OPENING_PARENTHESIS: {
    } break;
    case FUN_NAME_PARSE_INPUT_CLOSING_PARENTHESIS: {
    } break;
    case FUN_NAME_PARSE_INPUT_SEMICOLON: {
    } break;
    case FUN_NAME_PARSE_INPUT_NEW_LINE: {
        res = true;
    } break;
    case FUN_NAME_PARSE_INPUT_CARRIAGE_RETURN: {
        res = true;
    } break;
    case FUN_NAME_PARSE_INPUT_OPENING_BRACE: {
    } break;
    case FUN_NAME_PARSE_INPUT_CLOSING_BRACE: {
        // Node->brace_close_cnt++;
        // Node->brace_cnt--;
    } break;
    default:
        break;
    }
    return res;
}

static bool parse_func_name_proc_fun_return_type(cGeneratorHandle_t* Node) {
    bool res = false;
    return res;
}

static bool parse_func_name_proc_fun_name(cGeneratorHandle_t* Node) {
    bool res = false;
    return res;
}

static bool parse_func_name_proc_fun_arguments(cGeneratorHandle_t* Node) {
    bool res = false;
    return res;
}

static bool parse_func_name_proc_fun_body(cGeneratorHandle_t* Node) {
    bool res = false;
    return res;
}

bool code_style_check_global_proto_proc_char(cGeneratorHandle_t* Node, char letter) {
    bool res = false;
    if(Node) {
        Node->letter_cur = letter;
        Node->input = fund_func_classify_letter(letter);

        switch(Node->input) {
        case FUN_NAME_PARSE_INPUT_OPENING_BRACE: {
            Node->brace_open_cnt++;
            Node->brace_cnt++;
            if(1 == Node->brace_cnt) {
                Node->function_cnt++;
            }
        } break;

        case FUN_NAME_PARSE_INPUT_CLOSING_BRACE: {
            Node->brace_close_cnt++;
            Node->brace_cnt--;

        } break;

        default:
            break;
        }

        switch(Node->state) {
        case FUN_NAME_PARSE_STATE_IDLE:
            res = parse_func_name_proc_idle(Node);
            break;
        case FUN_NAME_PARSE_STATE_TYPE:
            res = parse_func_name_proc_fun_return_type(Node);
            break;
        case FUN_NAME_PARSE_STATE_FUNCTION_NAME:
            res = parse_func_name_proc_fun_name(Node);
            break;
        case FUN_NAME_PARSE_STATE_ARGUMENT:
            res = parse_func_name_proc_fun_arguments(Node);
            break;
        case FUN_NAME_PARSE_STATE_FUNCTION_BODY:
            res = parse_func_name_proc_fun_body(Node);
            break;

        default:
            break;
        }
        res = true;

        Node->letter_prev = letter;
    }
    return res;
}

bool code_style_check_global_proto_proc_line(cGeneratorHandle_t* Node, char* line) {
    bool res = false;
    if(Node) {
        if(line) {
            size_t len = strlen(line);
            LOG_DEBUG(C_GENERATOR, "ProcLine,Len:%u,Line:[%s]", len, line);
            if('/' != line[0]) {
                if('/' != line[1]) {
                    res = true;
                    uint32_t i = 0;
                    for(i = 0; i < len; i++) {
                        res = code_style_check_global_proto_proc_char(Node, line[i]);
                    }
                }
            }
        }
    }
    return res;
}

bool func_name_parse_fsm_init(cGeneratorHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->state = FUN_NAME_PARSE_STATE_IDLE;
        Node->brace_open_cnt = 0;
        Node->brace_close_cnt = 0;
        Node->function_cnt = 0;
        res = true;
    }
    return res;
}
