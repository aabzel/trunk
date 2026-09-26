#include "running_line_config.h"

#include "data_utils.h"

static char Text1[80] = "Te,";
static char Text2[80] = "Text1,";
static RunningLineChar_t Symbol1[80];
static RunningLineChar_t Symbol2[80];

static char WindowText1[14] = "";
static char WindowText2[14] = "";

#ifdef HAS_RUNNING_LINE_4
static char Text4[80] = "Text4,Text3,Text2,Text1,";
static RunningLineChar_t Symbol4[80];
static char WindowText4[14] = "";
#endif

#ifdef HAS_RUNNING_LINE_3
static char Text3[80] = "Text3,Text2,Text1,";
static RunningLineChar_t Symbol3[80];
static char WindowText3[14] = "";
#endif

const RunningLineConfig_t SECTION_CFG_DATA RunningLineConfig[] = {
    {
        .num = 1,
        .valid = true,
        .Text = Text1,
        .size = sizeof(Text1),
        .WindowText = WindowText1,
        .window_size = sizeof(WindowText1),
        .duration_ms = 100,
        .Symbol = Symbol1,
    },
    {
        .num = 2,
        .valid = true,
        .Text = Text2,
        .size = sizeof(Text2),
        .WindowText = WindowText2,
        .window_size = sizeof(WindowText2),
        .duration_ms = 200,
        .Symbol = Symbol2,
    },
#ifdef HAS_RUNNING_LINE_3
    {
        .num = 3,
        .valid = true,
        .Text = Text3,
        .size = sizeof(Text3),
        .WindowText = WindowText3,
        .window_size = sizeof(WindowText3),
        .duration_ms = 300,
        .Symbol = Symbol3,
    },
#endif
#ifdef HAS_RUNNING_LINE_4
    {
        .num = 4,
        .valid = true,
        .Text = Text4,
        .size = sizeof(Text4),
        .WindowText = WindowText4,
        .window_size = sizeof(WindowText4),
        .duration_ms = 400,
        .Symbol = Symbol4,
    },
#endif
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
#ifdef HAS_RUNNING_LINE_3
    {
        .num = 3,
        .valid = true,
    },
#endif
#ifdef HAS_RUNNING_LINE_4
    {
        .num = 4,
        .valid = true,
    },
#endif
};


COMPONENT_GET_CNT(RunningLine, running_line)
