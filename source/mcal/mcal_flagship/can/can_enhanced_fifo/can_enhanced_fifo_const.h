#ifndef CAN_ENHANCED_FIFO_CONST_H
#define CAN_ENHANCED_FIFO_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#define FLEXCAN_FILTER_ELEMENT_COUNT 32


/* filter scheme */
typedef enum {
    CAN_FSCH_MASK_AND_FILTER = 0, /* filter scheme is based on mask and filter*/
    CAN_FSCH_RANGE = 1, /* filter scheme is based on range.*/
    CAN_FSCH_TWO_IDS = 2, /* filter scheme is based on two filters without masks*/
    CAN_FSCH3 = 3, /* --*/
    CAN_FSCH_UNDEF = 4,
}CanFSCH_t;


#ifdef __cplusplus
}
#endif

#endif /* CAN_ENHANCED_FIFO_CONST_H  */




