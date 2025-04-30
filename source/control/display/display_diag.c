#include "display_diag.h"

#include <stdio.h>

#include "display_drv.h"
#include "convert.h"
#include "log.h"

static const char* DataMatrixVal2Color(char val){
	const char* name="red";
	switch(val){
	case 0:  name="white";break;
	case 1:  name="black";break;
	default:name="reg";break;
	}
	return name;
}


static bool display_render_segment(uint16_t x, int16_t p, uint8_t segment, DisplayHandle_t* Node){
    bool res = false;
    if (segment) {
        LOG_DEBUG(DISPLAY, "(%d,%d):RenderSegment 0x%x=%s",x,p*8,segment, utoa_bin8(segment));
    }
    int8_t sy = 0;
    for(sy=0; sy<=7; sy++) {
        int16_t y = - sy - p*8;
        char CommonAttributes[200] = "";
        sprintf(CommonAttributes,"[height=%f][width=%f][shape=square][label=\"\"][style=filled]",Node->pixel_size,Node->pixel_size);
        if(    segment&(1<<sy)    ) {
            /*Pix On*/
            fprintf(Node->file_ptr, "node_%u %s[color=%s][pos =\"%f,%f!\"];\n",Node->pix_cnt,CommonAttributes,DataMatrixVal2Color(0),((double)x)*Node->pixel_size,((double)y)*Node->pixel_size);
        } else {
            /*Pix Off*/
            fprintf(Node->file_ptr, "node_%u %s[color=%s][pos =\"%f,%f!\"];\n",Node->pix_cnt,CommonAttributes,DataMatrixVal2Color(1),((double)x)*Node->pixel_size,((double)y)*Node->pixel_size);
        }
        Node->pix_cnt++;
    }
    return res;
}

#define DISPLAY_SVG_RENDER "C:/Program Files/Google/Chrome/Application/chrome.exe"

bool display_render_ll(DisplayHandle_t* Node , uint8_t* FrameBuffer, uint32_t size){
    bool res = false;
    LOG_DEBUG(DISPLAY, "Render Width:%u",Node->width);
    if(Node) {
        Node->file_ptr = NULL;
        char FileNameGv[80]="";
        char FileNameSvg[80]="";
        char FileNamePng[80]="";
        Node->pix_cnt = 1;
        snprintf(FileNameGv,sizeof(FileNameGv),"%s.gv",Node->name);
        snprintf(FileNameSvg,sizeof(FileNameSvg),"%s.svg",Node->name);
        snprintf(FileNamePng,sizeof(FileNamePng),"%s.png",Node->name);
        Node->file_ptr = fopen(FileNameGv, "w");
        if(Node->file_ptr) {
            fprintf(Node->file_ptr, "digraph Display {\n");
            int16_t p = 0;
            for(p=0;p<Node->page_cnt;p++) {
                uint16_t x = 0;
                for(x=0;x<Node->width;x++) {
                      uint8_t segment = FrameBuffer[(p*Node->width)+x];
                      res = display_render_segment(x,p,segment,Node);
                }
            }
            fprintf(Node->file_ptr, "}\n");
            fclose(Node->file_ptr);
        }

        char CmdCommand[200] = "";
        sprintf(CmdCommand, "start /B dot.exe -Kneato -Tpng  %s -o %s", FileNameGv,FileNamePng);
        res = win_cmd_run(CmdCommand);
        // sprintf(CmdCommand, "start /B dot.exe -Kneato -Tsvg  %s -o %s", FileNameGv,FileNameSvg);
        //sprintf(CmdCommand, "start dot.exe -Kneato -Tsvg  %s -o %s", FileNameGv,FileNameSvg);
        //res = win_cmd_run(CmdCommand);
        // res = win_cmd_run("start chrome.exe -open out.svg");
        //sprintf(CmdCommand, "start \"%s\" -open %s",DISPLAY_SVG_RENDER,FileNameSvg);
        //sprintf(CmdCommand, "start \"%s\" -open %s",DISPLAY_SVG_RENDER,FileNameSvg);
        //res = win_cmd_run(CmdCommand);
    }
    return res;
}

