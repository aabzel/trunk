#include "iec16022_drv.h"


#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "win_utils.h"
#include "array_diag.h"
#include "iec16022ecc200.h"

bool iec16022_encode(uint8_t* array, size_t size, char* file_name) {
    bool res = false;
    int w = 0, h = 0;
    char *enc = NULL;
    char qraphviz_file_name[100]={0};
    unsigned char *ret = iec16022ecc200f(&w, &h, &enc, size, array, NULL, NULL, NULL, 0);
    if(ret){
        LOG_INFO(IEC16022, "EncodeOk,w:%d,h:%d Enc:[%s],Ret:[%s]",w,h,enc,ret);
        print_hex(ret,w*h);
        res = iec16022_print_cli(ret, w , h);

        snprintf(qraphviz_file_name, sizeof(qraphviz_file_name), "gv_%s.gv",  file_name);
        res = iec16022_print_graphviz(ret ,w , h, qraphviz_file_name);
        free(ret);

        char CmdCommand[200] = "";
        sprintf(CmdCommand, "start dot.exe -Kneato -Tsvg %s -o svg_%s.svg", qraphviz_file_name, file_name);
        res = win_cmd_run(CmdCommand);
        // res = win_cmd_run("start chrome.exe -open out.svg");
        //sprintf(CmdCommand, "start \"%s\" -open %s.svg", SVG_RENDER, file_name);
        //res = win_cmd_run(CmdCommand);
    }else {
        LOG_ERROR(IEC16022, "EncodeErr");
    }
    if(enc){
        free(enc);
    }
    return res;
}
