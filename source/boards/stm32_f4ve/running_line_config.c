#include "running_line_config.h"

#include "data_utils.h"

//#define RUN_LINE_SIZE 210
#define RUN_LINE_SIZE1 200
static char Text1[RUN_LINE_SIZE1] = "Te,";
static  RunningLineChar_t Symbol1[RUN_LINE_SIZE1];

static char Text2[160] = "Text2,";
static  RunningLineChar_t Symbol2[160];

static char Text3[250] = "Text3,Text3,Text3,";
static  RunningLineChar_t Symbol3[250];

static char Text4[100] = "Text4,Text4,Text4,Text4,";
static  RunningLineChar_t Symbol4[100];

#define WINDOW_TEXT_SIZE 16
static char WindowText1[WINDOW_TEXT_SIZE] = "";
static char WindowText2[WINDOW_TEXT_SIZE] = "";
static char WindowText3[WINDOW_TEXT_SIZE] = "";
static char WindowText4[WINDOW_TEXT_SIZE] = "";

const RunningLineConfig_t RunningLineConfig[] = {
    {
        .num = 1,
        .valid = true,
        .Text = Text1,
        .Symbol = Symbol1,
        .size = sizeof(Text1),
        .WindowText = WindowText1,
        .window_size = sizeof(WindowText1),
        .duration_ms = 100,
    },
    {
        .num = 2,
        .valid = true,
        .Text = Text2,
        .Symbol = Symbol2,
        .size = sizeof(Text2),
        .WindowText = WindowText2,
        .window_size = sizeof(WindowText2),
        .duration_ms = 100,
    },
    {
        .num = 3,
        .valid = true,
        .Text = Text3,
        .Symbol = Symbol3,
        .size = sizeof(Text3),
        .WindowText = WindowText3,
        .window_size = sizeof(WindowText3),
        .duration_ms = 50,
    },
    {
        .num = 4,
        .valid = true,
        .Text = Text4,
        .Symbol = Symbol4,
        .size = sizeof(Text4),
        .WindowText = WindowText4,
        .window_size = sizeof(WindowText4),
        .duration_ms = 25,
    },
};

RunningLineHandle_t RunningLineInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
    {
        .num = 3,
        .valid = true,
    },
    {
        .num = 4,
        .valid = true,
    },
};

uint32_t running_line_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(RunningLineInstance);
    cnt2 = ARRAY_SIZE(RunningLineConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
