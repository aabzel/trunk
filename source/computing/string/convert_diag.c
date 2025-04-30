#include "convert_diag.h"

#include <stdint.h>
#include <stdio.h>

const char* NumberParserState2Str(ParseNumberStates_t state){
    const char* name="?";
    switch((uint8_t)state){
    case PARSE_NUMBER_STATE_PARSE_SIGN:name="ParseSign"; break;
    case PARSE_NUMBER_STATE_PARSE_INTEGER:name="ParseInt"; break;
    case PARSE_NUMBER_STATE_PARSE_FRACTION:name="ParseFrac"; break;
    case PARSE_NUMBER_STATE_DONE:name="Done"; break;
    case PARSE_NUMBER_STATE_PARSE_EXPONENTA_SIGN:name="ParseExpSign"; break;
    case PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER:name="ParseExpInt"; break;

    }
    return name;
}

const char*Sign2Str(int8_t sign){
    const char* name="?";
    switch(sign){
        case 1:name="+"; break;
        case -1:name="-"; break;
    }
    return name;
}

const char* SymbolToStr(char symbol){
    static char text[20] ={};
    switch(symbol) {
        case '\n': strcpy(text,"NewLine"); break;
        case '\r': strcpy(text,"CaretRet"); break;
        default :{
            text[0]=symbol;
            text[1]=0;
        }
        break;
    }
    return text ;
}

char* NumberParserFsm2Str(const Text2NumberFsm_t * const Node){
    static char name[300]="";
    sprintf(name,"[%s] State:%s, ManSign %s Int:%Le Frac:%f ,Order %u ExpSign:%s ExpInt %u Value:%f",
            SymbolToStr(Node->cur_letter),
            NumberParserState2Str(Node->state),
            Sign2Str(Node->sign),
            Node->integer,
            Node->fraction,
            Node->fraction_order,
            Sign2Str(Node->exponent_sign),
            Node->exponent_integer,
            Node->value
            );
    return name;
}


