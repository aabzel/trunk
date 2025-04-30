#include "running_line_config.h"

#include "data_utils.h"

static char Text1[80] = "Te,";
static char Text2[80] = "Text2,";
static char Text3[80] = "Text3,Text3,Text3,";
static char Text4[80] = "Text4,Text4,Text4,Text4,";

static char WindowText1[10] = "";
static char WindowText2[10] = "";
static char WindowText3[10] = "";
static char WindowText4[10] = "";

const RunningLineConfig_t RunningLineConfig[] = {
    {
        .num = 1,
        .valid = true,
        .Text = Text1,
        .size = sizeof(Text1),
        .WindowText = WindowText1,
        .window_size = sizeof(WindowText1),
        .duration_ms = 100,
    },
    {
        .num = 2,
        .valid = true,
        .Text = Text2,
        .size = sizeof(Text2),
        .WindowText = WindowText2,
        .window_size = sizeof(WindowText2),
        .duration_ms = 300,
    },
    {
        .num = 3,
        .valid = true,
        .Text = Text3,
        .size = sizeof(Text3),
        .WindowText = WindowText3,
        .window_size = sizeof(WindowText3),
        .duration_ms = 200,
    },
    {
        .num = 4,
        .valid = true,
        .Text = Text4,
        .size = sizeof(Text4),
        .WindowText = WindowText4,
        .window_size = sizeof(WindowText4),
        .duration_ms = 100,
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
