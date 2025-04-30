#include "iec16022_diag.h"

#include <stdio.h>

#include "debug_info.h"
#include "log.h"
#include "win_utils.h"

bool iec16022_print_cli(unsigned char *ret ,int w , int h){
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(IEC16022,"Print");
    int32_t i,j;
    for(i=h-1;0<=i;i--){
       for(j=0;j<w;j++){
           cli_printf("%d",*(ret+i*w+j));
       }
   	   cli_printf(CRLF);
       res = true;
    }

    return res;
}



const char* DataMatrixVal2Color(char val){
	const char* name="red";
	switch(val){
	case 0:  name="white";break;
	case 1:  name="black";break;
	default:name="reg";break;
	}
	return name;
}

bool iec16022_print_graphviz(unsigned char *ret ,int w , int h, char* name){
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(IEC16022,"GenerateGraphviz:[%s]",name);

    FILE* file_ptr = NULL;
    file_ptr = fopen(name, "w");
    if(file_ptr) {
    	fprintf(file_ptr, "digraph DataMatrixCore {\n");
        uint32_t cnt = 1;
        int32_t y, x;
        for(y=h-1; 0<=y; y--) {
           for(x=0;x<w;x++) {
               char color=*(ret+y*w+x);
               fprintf(file_ptr, "node_%u [height=1][width=1][label=\" \"][shape=square][style=filled][color=%s][pos =\"%d,%d!\"];\n",cnt,DataMatrixVal2Color(color),x,y);
               cnt++;
           }
        }

        fprintf(file_ptr, "Text [shape=box][color=white][pos=\"5,-1!\"][label=\"%s\"] [fontsize=35]\n", name);

        fprintf(file_ptr, "}\n");
        fclose(file_ptr);
        res = true;
    }

    return res;
}


