#include "interval.h"

#include <stdlib.h>
#include <string.h>

#include "data_utils.h"
#include "interval_const.h"
#ifdef HAS_STABLE_SORT
#include "stable_sort.h"
#endif

#ifdef HAS_LOG
#include "log.h"
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
        // IntervalEDiag(INTERVAL, "In:", in);
#endif
        out->start = in->start;
        out->size = in->end - in->start;
#ifdef HAS_INTERVAL_DIAG
        // IntervalSDiag(INTERVAL, "Out:", out);
#endif
    }

    return res;
}

bool IntervalConvert_2_1(const IntervalS_t* const in, IntervalE_t* const out) {
    bool res = false;
    if(in) {
        if(out) {
#ifdef HAS_INTERVAL_DIAG
            // IntervalSDiag(INTERVAL, "In:", in);
#endif
            out->start = in->start;
            out->end = in->start + in->size;
#ifdef HAS_INTERVAL_DIAG
            // IntervalEDiag(INTERVAL, "Out:", out);
#endif
        }
    }
    return res;
}

int comp_points(const void* elem1, const void* elem2) {
    if((((IntervalPoints_t*)elem2)->val) < (((IntervalPoints_t*)elem1)->val))
        return 1;
    if((((IntervalPoints_t*)elem1)->val) < (((IntervalPoints_t*)elem2)->val))
        return -1;
    return 0;
}

int comp_num(const void* elem1, const void* elem2) {
    int ret = 0;
    if((((IntervalPoints_t*)elem2)->num) < (((IntervalPoints_t*)elem1)->num))
        ret = 1;
    if((((IntervalPoints_t*)elem1)->num) < (((IntervalPoints_t*)elem2)->num))
        ret = -1;
    return ret;
}

int comp_bracket(const void* elem1, const void* elem2) {
    int ret = 0;
    if((((IntervalPoints_t*)elem2)->type) < (((IntervalPoints_t*)elem1)->type))
        ret = 1;
    if((((IntervalPoints_t*)elem1)->type) < (((IntervalPoints_t*)elem2)->type))
        ret = -1;
    return ret;
}

#ifdef HAS_STABLE_SORT

#endif

bool interval_is_a_in_b(const IntervalE_t* const pA, const IntervalE_t* const pB) {
    bool res = false;
    LOG_DEBUG(INTERVAL, "%u-%u;%u-%u", pA->start, pA->end, pB->start, pB->end);
    if(pB->start <= pA->start) {
        if(pA->end <= pB->end) {
            res = true;
        }
    }
    return res;
}

bool interval_is_merge(IntervalE_t* const pA, IntervalE_t* const pB) {
    bool res = false;
    res = interval_is_a_in_b(pA, pB);
    if(false == res) {
        res = interval_is_a_in_b(pB, pA);
    }
    return res;
}

/*Is one interval within another?*/
bool interval_is_embrace(const IntervalE_t* const pA, const IntervalE_t* const pB) {
    bool res = false;
    LOG_DEBUG(INTERVAL, "%u-%u;%u-%u", pA->start, pA->end, pB->start, pB->end);
    res = interval_is_a_in_b(pA, pB);
    if(false == res) {
        res = interval_is_a_in_b(pB, pA);
    }
    return res;
}

bool interval_is_dock(const IntervalE_t* const pA, const IntervalE_t* const pB) {
    bool dock = false;
    if(pA->end == pB->start) {
        dock = true;
    }
    if(pB->end == pA->start) {
        dock = true;
    }
    return dock;
}

bool interval_merge(IntervalE_t* const A, IntervalE_t* const B, IntervalE_t* const Interval_new) {
    bool res = false;
    if(A && B && Interval_new) {
        IntervalPoints_t Point[4] = {0};
        Point[0].val = A->start;
        Point[0].type = INT_POINT_START;

        Point[1].val = A->end;
        Point[1].type = INT_POINT_END;

        Point[2].val = B->start;
        Point[2].type = INT_POINT_START;

        Point[3].val = B->end;
        Point[3].type = INT_POINT_END;

        qsort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points);
        /*TODO Add DIAG
         * IntervalDiag(Point, ARRAY_SIZE(Point))*/
        if(INT_POINT_START == Point[0].type) {
            Interval_new->start = Point[0].val;
            if(INT_POINT_END == Point[3].type) {
                Interval_new->end = Point[3].val;
                res = true;
            }
        }
    }

    return res;
}

#if 0
bool interval_intersect(const IntervalE_t* const A, const IntervalE_t* const B) {
    bool res = false;
    LOG_DEBUG(INTERVAL, "%u->%u; %u->%u", A->start, A->end, B->start, B->end);

    res = interval_is_merge(A, B);
    if(false == res) {

        IntervalPoints_t Point[4] = {0};
        Point[0].val = A->start;
        Point[0].type = INT_POINT_START;
        Point[0].num = 1;

        Point[1].val = A->end;
        Point[1].type = INT_POINT_END;
        Point[1].num = 1;

        Point[2].val = B->start;
        Point[2].type = INT_POINT_START;
        Point[2].num = 2;

        Point[3].val = B->end;
        Point[3].type = INT_POINT_END;
        Point[3].num = 2;

        merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_bracket);
        merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_num);
        merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points);

        uint32_t i = 0;
        int32_t cnt = 0;
        for(i = 0; i < ARRAY_SIZE(Point); i++) {
            switch(Point[i].type) {
            case INT_POINT_START:
                cnt++;
                break;
            case INT_POINT_END:
                cnt--;
                break;
            default:
                break;
            }
            LOG_DEBUG(INTERVAL, "%u,Dot:%s,CNT:%d", i, DotToStr(&Point[i]), cnt);
            if(1 < cnt) {
#ifdef HAS_LOG
                LOG_DEBUG(INTERVAL, "SpotCtoss:%u", Point[i].val);
#endif

                res = true;
                // break;
            }
        }
    }

    return res;
}
#endif

#ifdef HAS_STABLE_SORT
bool interval_intersect_continuum(const IntervalE_t* const A, const IntervalE_t* const B) {
    bool res = false;
    LOG_DEBUG(INTERVAL, "%u->%u; %u->%u", A->start, A->end, B->start, B->end);
    bool spot_start = false;
    bool spot_end = false;

    IntervalE_t commom_e = {
        .start = 0,
        .end = 0,
    };
    IntervalPoints_t Point[4] = {0};
    Point[0].val = A->start;
    Point[0].type = INT_POINT_START;
    Point[0].num = 1;

    Point[1].val = A->end;
    Point[1].type = INT_POINT_END;
    Point[1].num = 1;

    Point[2].val = B->start;
    Point[2].type = INT_POINT_START;
    Point[2].num = 2;

    Point[3].val = B->end;
    Point[3].type = INT_POINT_END;
    Point[3].num = 2;

    /*From Small to Big*/
    merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_bracket);
    // IntervalDiagPoints(Point, ARRAY_SIZE(Point));
    merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_num);
    // IntervalDiagPoints(Point, ARRAY_SIZE(Point));
    merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points);
    // IntervalDiagPoints(Point, ARRAY_SIZE(Point));

    int32_t i = 0;
    int32_t line_cnt = 0;
    for(i = 0; i < ARRAY_SIZE(Point); i++) {
        switch(Point[i].type) {
        case INT_POINT_START:
            line_cnt++;
            break;
        case INT_POINT_END:
            line_cnt--;
            break;
        default:
            break;
        }

#ifdef HAS_LOG
        LOG_DEBUG(INTERVAL, "Dot:%u,X:%u CNT:%d", i, Point[i].val, line_cnt);
#endif
        if(2 == line_cnt) {
            if(false == spot_start) {
#ifdef HAS_LOG
                LOG_DEBUG(INTERVAL, "SpotStart %u", Point[i].val);
#endif
                commom_e.start = Point[i].val;
                spot_start = true;
            }
        }

        if(line_cnt < 2) {
            if(spot_start) {
                if(false == spot_end) {
                    spot_end = true;
#ifdef HAS_LOG
                    LOG_DEBUG(INTERVAL, "SpotEnd %u", Point[i].val);
#endif
                    commom_e.end = Point[i].val;
                }
            }
        }
    }

    IntervalS_t commom_s = {0};
    res = IntervalConvert_e_s(&commom_e, &commom_s);
#ifdef HAS_INTERVAL_DIAG
    // IntervalSDiag(INTERVAL, "Commom", &commom_s);
#endif

    LOG_PARN(INTERVAL, "IntersectSize:%u", commom_s.size);
    if(commom_s.size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

#endif

#if 0
bool interval_merge(IntervalE_t* const A, IntervalE_t* const B, IntervalE_t* const Interval_new) {
    bool res = false;
    if(A && B && Interval_new) {
        IntervalPoints_t Point[4] = {0};
        Point[0].val = A->start;
        Point[0].type = INT_POINT_START;

        Point[1].val = A->end;
        Point[1].type = INT_POINT_END;

        Point[2].val = B->start;
        Point[2].type = INT_POINT_START;

        Point[3].val = B->end;
        Point[3].type = INT_POINT_END;

        qsort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points);
        /*TODO Add DIAG
         * IntervalDiag(Point, ARRAY_SIZE(Point))*/
        if(INT_POINT_START == Point[0].type) {
            Interval_new->start = Point[0].val;
            if(INT_POINT_END == Point[3].type) {
                Interval_new->end = Point[3].val;
                res = true;
            }
        }
    }

    return res;
}
#endif

#ifdef HAS_STABLE_SORT
/*
  A 0000000000001111111000000
  B 0001111110000000000000000
 *
 * */
bool interval_intersect(const IntervalE_t* const A, const IntervalE_t* const B) {
    bool res = false;

    IntervalPoints_t Point[4] = {0};
    Point[0].val = A->start;
    Point[0].type = INT_POINT_START;
    Point[0].num = 1;

    Point[1].val = A->end;
    Point[1].type = INT_POINT_END;
    Point[1].num = 1;

    Point[2].val = B->start;
    Point[2].type = INT_POINT_START;
    Point[2].num = 2;

    Point[3].val = B->end;
    Point[3].type = INT_POINT_END;
    Point[3].num = 2;

    res = merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_bracket);
    res = merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_num) && res;
    res = merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points) && res;

    uint32_t i = 0;
    int32_t cnt = 0;
    for(i = 0; i < ARRAY_SIZE(Point); i++) {
        switch(Point[i].type) {
        case INT_POINT_START:
            cnt++;
            break;
        case INT_POINT_END:
            cnt--;
            break;
        default:
            break;
        }
        if(1 < cnt) {
            res = true;
            break;
        }
    }

    return res;
}
#endif

#ifdef HAS_STABLE_SORT
bool intervals_intersect(const IntervalE_t* A, const IntervalE_t* B) {
    bool res = false;
    LOG_DEBUG(INTERVAL, "%u->%u; %u->%u", A->start, A->end, B->start, B->end);
    bool spot_start = false;
    bool spot_end = false;

    IntervalE_t commom_e = {
        .start = 0,
        .end = 0,
    };
    IntervalPoints_t Point[4] = {0};
    Point[0].val = A->start;
    Point[0].type = INT_POINT_START;
    Point[0].num = 1;

    Point[1].val = A->end;
    Point[1].type = INT_POINT_END;
    Point[1].num = 1;

    Point[2].val = B->start;
    Point[2].type = INT_POINT_START;
    Point[2].num = 2;

    Point[3].val = B->end;
    Point[3].type = INT_POINT_END;
    Point[3].num = 2;

    /*From Small to Big*/
    res = merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_bracket);
    // IntervalDiagPoints(Point, ARRAY_SIZE(Point));
    res = merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_num) && res;
    // IntervalDiagPoints(Point, ARRAY_SIZE(Point));
    res = merge_sort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points) && res;
    //  IntervalDiagPoints(Point, ARRAY_SIZE(Point));

    int32_t i = 0;
    int32_t line_cnt = 0;
    for(i = 0; i < ARRAY_SIZE(Point); i++) {
        switch(Point[i].type) {
        case INT_POINT_START:
            line_cnt++;
            break;
        case INT_POINT_END:
            line_cnt--;
            break;
        default:
            break;
        }

#ifdef HAS_LOG
        LOG_DEBUG(INTERVAL, "Dot:%u,X:%u CNT:%d", i, Point[i].val, line_cnt);
#endif
        if(2 == line_cnt) {
            if(false == spot_start) {
#ifdef HAS_LOG
                LOG_DEBUG(INTERVAL, "SpotStart %u", Point[i].val);
#endif
                commom_e.start = Point[i].val;
                spot_start = true;
            }
        }

        if(line_cnt < 2) {
            if(spot_start) {
                if(false == spot_end) {
                    spot_end = true;
#ifdef HAS_LOG
                    LOG_DEBUG(INTERVAL, "SpotEnd %u", Point[i].val);
#endif
                    commom_e.end = Point[i].val;
                }
            }
        }
    }

    IntervalS_t commom_s = {0};
    res = IntervalConvert_e_s(&commom_e, &commom_s);
#ifdef HAS_INTERVAL_DIAG
    // IntervalSDiag(INTERVAL, "Commom", &commom_s);
#endif

    LOG_PARN(INTERVAL, "IntersectSize:%u", commom_s.size);
    if(commom_s.size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif

#ifdef HAS_STABLE_SORT
bool intervals_shared(IntervalE_t* A, IntervalE_t* B) {
    bool res = false;
    bool spot_start = false;
    bool spot_end = false;

    IntervalE_t commom_e = {
        .start = 0,
        .end = 0,
    };
    IntervalPoints_t Point[4];
    Point[0].val = A->start;
    Point[0].type = INT_POINT_START;

    Point[1].val = A->end;
    Point[1].type = INT_POINT_END;

    Point[2].val = B->start;
    Point[2].type = INT_POINT_START;

    Point[3].val = B->end;
    Point[3].type = INT_POINT_END;

    /*From Small to Big*/
    qsort(Point, ARRAY_SIZE(Point), sizeof(IntervalPoints_t), comp_points);

    int32_t i = 0;
    int32_t line_cnt = 0;
    for(i = 0; i < ARRAY_SIZE(Point); i++) {
        switch(Point[i].type) {
        case INT_POINT_START:
            line_cnt++;
            break;
        case INT_POINT_END:
            line_cnt--;
            break;

        default:

            break;
        }

#ifdef HAS_LOG
        LOG_DEBUG(INTERVAL, "Dot:%u,X:%u CNT:%d", i, Point[i].val, line_cnt);
#endif
        if(2 == line_cnt) {
            if(false == spot_start) {
#ifdef HAS_LOG
                LOG_DEBUG(INTERVAL, "SpotStart %u", Point[i].val);
#endif
                commom_e.start = Point[i].val;
                spot_start = true;
            }
        }

        if(line_cnt < 2) {
            if(spot_start) {
                if(false == spot_end) {
                    spot_end = true;
#ifdef HAS_LOG
                    LOG_DEBUG(INTERVAL, "SpotEnd %u", Point[i].val);
#endif
                    commom_e.end = Point[i].val;
                }
            }
        }
    }

    IntervalS_t intervalAS = {0};
    IntervalS_t intervalBS = {0};
    IntervalS_t commom_s = {0};
    res = IntervalConvert_e_s(B, &intervalBS);
    res = IntervalConvert_e_s(A, &intervalAS);
    res = IntervalConvert_e_s(&commom_e, &commom_s);
#ifdef HAS_INTERVAL_DIAG
    // IntervalSDiag(INTERVAL, "Commom", &commom_s);
#endif

    uint32_t min_size = 0;
    min_size = MATH_MIN(intervalAS.size, intervalBS.size);
    LOG_DEBUG(INTERVAL, "min_size %u", min_size);
    if(commom_s.size == min_size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif
