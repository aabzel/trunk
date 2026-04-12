#include "interval_diag.h"

#include "diag_inc.h"
#include "interval_types.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

bool IntervalEDiag(log_level_t level, char* prefix, const IntervalE_t* const interval) {
    bool res = false;
    if(interval) {
        log_write(level, INTERVAL, "%s:[%u...%u]", prefix, interval->start, interval->end);
        res = false;
    }
    return res;
}

bool IntervalSDiag(log_level_t level, char* prefix, const IntervalS_t* const interval) {
    bool res = false;
    if(interval) {
        log_write(level, INTERVAL, "%s:[%u:+%u", prefix, interval->start, interval->size);
        res = false;
    }
    return res;
}

const char* BracketToStr(const IntervalPoint_t type) {
    const char* name = "?";
    switch(type) {
    case INT_POINT_START:
        name = "[";
        break;
    case INT_POINT_END:
        name = "]";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}

const char* DotToStr(const IntervalPoints_t* const Dot) {
    strcpy(text, "");
    if(Dot) {
        snprintf(text, sizeof(text), "%sX:%u", text, Dot->val);
        snprintf(text, sizeof(text), "%sN:%u", text, Dot->num);
        snprintf(text, sizeof(text), "%s%s", text, BracketToStr(Dot->type));
    }
    return text;
}

bool IntervalDiagPoints(const IntervalPoints_t* const Point, const uint32_t cnt) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "X"},
        {5, "N"},
        {5, "{}"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        char log_line[150];
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Point[i].val);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Point[i].num);
        snprintf(log_line, sizeof(log_line), "%s %3s " TSEP, log_line, BracketToStr(Point[i].type));
        cli_printf("%s" CRLF, log_line);
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
