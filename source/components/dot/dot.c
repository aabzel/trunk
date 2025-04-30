#include "dot.h"

#include "log.h"


bool dot_header(FILE *file, char* dir){
    bool res = false;
    if(file) {
    	res = true;
        fprintf(file,"strict digraph G {"CRLF);
        fprintf(file,"   rankdir=%s"CRLF, dir);
        /* fprintf(file,"   splines=ortho"CRLF);*/
        fprintf( file, "    node [shape=box]"CRLF);
    }
	return res;
}

bool dot_tail(FILE *file) {
    bool res = false;
    if(file) {
        fprintf(file,"}"CRLF);
        res = true;
    }
	return res;
}

