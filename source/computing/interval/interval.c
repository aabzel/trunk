#include "interval.h"

#include <stdlib.h>
#include <string.h>

#include "data_utils.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

bool is_interval_e(const IntervalE_t* const Interval) {
    bool res = false;
    if(Interval->start < Interval->end) {
        res = true;
    }
    return res;
}

bool IntervalConvert_e_s(const IntervalE_t* const in, IntervalS_t* const out) {
    bool res = false;
    res = is_interval_e(in);
    if(res) {
#ifdef HAS_INTERVAL_DIAG
        IntervalEDiag(LOG_LEVEL_DEBUG, "In:", in);
#endif
        out->start = in->start;
        out->size = in->end - in->start;
#ifdef HAS_INTERVAL_DIAG
        IntervalSDiag(LOG_LEVEL_DEBUG, "Out:", out);
#endif
    }

    return res;
}

bool IntervalConvert_2_1(const IntervalS_t* const in, IntervalE_t* const out) {
    bool res = false;
    if(in) {
        if(out) {
#ifdef HAS_INTERVAL_DIAG
            IntervalSDiag(LOG_LEVEL_DEBUG, "In:", in);
#endif
            out->start = in->start;
            out->end = in->start + in->size;
#ifdef HAS_INTERVAL_DIAG
            IntervalEDiag(LOG_LEVEL_DEBUG, "Out:", out);
#endif
        }
    }
    return res;
}

static int comp_points(const void* elem1, const void* elem2) {
    if((((IntervalPoints_t*)elem2)->val) < (((IntervalPoints_t*)elem1)->val))
        return 1;
    if((((IntervalPoints_t*)elem1)->val) < (((IntervalPoints_t*)elem2)->val))
        return -1;
    return 0;
}

bool intervals_merge(IntervalE_t* const Interval_a, IntervalE_t* const Interval_b, IntervalE_t* const Interval_new) {
    bool res = false;
    if(Interval_a && Interval_b && Interval_new) {
        IntervalPoints_t IntervalPoints[4] = {0};
        IntervalPoints[0].val = Interval_a->start;
        IntervalPoints[0].type = INT_POINT_START;

        IntervalPoints[1].val = Interval_a->end;
        IntervalPoints[1].type = INT_POINT_END;

        IntervalPoints[2].val = Interval_b->start;
        IntervalPoints[2].type = INT_POINT_START;

        IntervalPoints[3].val = Interval_b->end;
        IntervalPoints[3].type = INT_POINT_END;

        qsort(IntervalPoints, ARRAY_SIZE(IntervalPoints), sizeof(IntervalPoints_t), comp_points);
        /*TODO Add DIAG
         * IntervalDiag(IntervalPoints, ARRAY_SIZE(IntervalPoints))*/
        if(INT_POINT_START == IntervalPoints[0].type) {
            Interval_new->start = IntervalPoints[0].val;
            if(INT_POINT_END == IntervalPoints[3].type) {
                Interval_new->end = IntervalPoints[3].val;
                res = true;
            }
        }
    }

    return res;
}

/*
  Interval_a 0000000000001111111000000
  Interval_b 0001111110000000000000000
 *
 * */
bool intervals_overlaps(IntervalE_t* Interval_a, IntervalE_t* Interval_b) {
    bool res = false;
    IntervalPoints_t IntervalPoints[4];
    IntervalPoints[0].val = Interval_a->start;
    IntervalPoints[0].type = INT_POINT_START;

    IntervalPoints[1].val = Interval_a->end;
    IntervalPoints[1].type = INT_POINT_END;

    IntervalPoints[2].val = Interval_b->start;
    IntervalPoints[2].type = INT_POINT_START;

    IntervalPoints[3].val = Interval_b->end;
    IntervalPoints[3].type = INT_POINT_END;

    qsort(IntervalPoints, ARRAY_SIZE(IntervalPoints), sizeof(IntervalPoints_t), comp_points);

    uint32_t i = 0;
    int32_t cnt = 0;
    for(i = 0; i < ARRAY_SIZE(IntervalPoints); i++) {
        switch(IntervalPoints[i].type) {
        case INT_POINT_START:
            cnt++;
            break;
        case INT_POINT_END:
            cnt--;
            break;
        }
        if(1 < cnt) {
            res = true;
            break;
        }
    }

    return res;
}

bool intervals_shared(IntervalE_t* Interval_a, IntervalE_t* Interval_b) {
    bool res = false;
    bool spot_start = false;
    bool spot_end = false;

    IntervalE_t commom_e = {
        .start = 0,
        .end = 0,
    };
    IntervalPoints_t IntervalPoints[4];
    IntervalPoints[0].val = Interval_a->start;
    IntervalPoints[0].type = INT_POINT_START;

    IntervalPoints[1].val = Interval_a->end;
    IntervalPoints[1].type = INT_POINT_END;

    IntervalPoints[2].val = Interval_b->start;
    IntervalPoints[2].type = INT_POINT_START;

    IntervalPoints[3].val = Interval_b->end;
    IntervalPoints[3].type = INT_POINT_END;

    /*From Small to Big*/
    qsort(IntervalPoints, ARRAY_SIZE(IntervalPoints), sizeof(IntervalPoints_t), comp_points);

    uint32_t i = 0;
    int32_t line_cnt = 0;
    for(i = 0; i < ARRAY_SIZE(IntervalPoints); i++) {
        switch(IntervalPoints[i].type) {
        case INT_POINT_START:
            line_cnt++;
            break;
        case INT_POINT_END:
            line_cnt--;
            break;
        }

#ifdef HAS_LOG
        LOG_DEBUG(INTERVAL, "i:%u X:%u CNT: %u", i, IntervalPoints[i].val, line_cnt);
#endif
        if(2 == line_cnt) {
            if(false == spot_start) {
#ifdef HAS_LOG
                LOG_DEBUG(INTERVAL, "SpotStart %u", IntervalPoints[i].val);
#endif
                commom_e.start = IntervalPoints[i].val;
                spot_start = true;
            }
        }

        if(line_cnt < 2) {
            if(spot_start) {
                if(false == spot_end) {
                    spot_end = true;
#ifdef HAS_LOG
                    LOG_DEBUG(INTERVAL, "SpotEnd %u", IntervalPoints[i].val);
#endif
                    commom_e.end = IntervalPoints[i].val;
                }
            }
        }
    }

    IntervalS_t intervalAS = {0};
    IntervalS_t intervalBS = {0};
    IntervalS_t commom_s = {0};
    res = IntervalConvert_e_s(Interval_b, &intervalBS);
    res = IntervalConvert_e_s(Interval_a, &intervalAS);
    res = IntervalConvert_e_s(&commom_e, &commom_s);
#ifdef HAS_INTERVAL_DIAG
    IntervalSDiag(LOG_LEVEL_DEBUG, "Commom", &commom_s);
#endif
    uint32_t min_size = 0;
    min_size = MIN(intervalAS.size, intervalBS.size);
    if(commom_s.size == min_size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
