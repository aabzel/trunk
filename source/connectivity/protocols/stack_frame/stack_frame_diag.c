#include "stack_frame_diag.h"

#include <stdio.h>
#include <string.h>

#include "stack_frame.h"
#include "log.h"

/**/

bool stack_frame_protocol_diag(uint8_t num) {
    bool res = false;
    StackFrameHandle_t* Node = StackFrameGetNode(num);
    if(Node) {
        LOG_INFO(STACK_FRAME, "ProtocolDiag %u", num);
        res = true;
    }
    return res;
}




const char* Content2Str(StackContentType_t content){
    const char* name = "?";
    switch( (uint8_t) content){
        case STACK_CONTENT_TYPE_OPERATION: name = "Oper";break;
        case STACK_CONTENT_TYPE_DOUBLE:name = "Double"; break;

    default: name = "Err";break;
    }
    return name;
}

/*op        1 sun  crc*/
/*data double 8 value crc*/
const char* StackFrame2Str(const uint8_t* const data, size_t size){
    static char text[80]="";
    if(data) {
        if(size) {
            /*TODO is valid frame?*/
            strcpy(text,"");
            snprintf(text,sizeof(text),"%s Cont:%s",text,Content2Str(data[0]));
            snprintf(text,sizeof(text),"%s Size:%u Byte",text,data[1]);
            switch(data[0]){
             case STACK_CONTENT_TYPE_OPERATION: {
                 snprintf(text,sizeof(text),"%s %s",text,Operation2Str(data[2]));
             }break;
             case STACK_CONTENT_TYPE_DOUBLE: {
                double value = 0.0;
                memcpy(&value,&data[2],sizeof(value ));
                 snprintf(text,sizeof(text),"%s %7.2f",text,value);
            }break;
            default: break;
            }
        }
    }
    return text;
}

