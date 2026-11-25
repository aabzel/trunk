#ifndef FC_CAN_ENHANCED_FIFO_TYPE_H
#define FC_CAN_ENHANCED_FIFO_TYPE_H

#include "can_enhanced_fifo_const.h"

/*
Table 89. Standard ID filter element with filter + mask scheme
 */
typedef union{
    uint32_t dword;
    struct{
        uint32_t STD_ID_MASK: 11; /* 10-0   */
        uint32_t RTR_MASK: 1; /* 11  */
        uint32_t RES1: 4; /* 15-12  */
        uint32_t STD_ID_FILTER: 11; /* 26-16   */
        uint32_t RTR_FILTER: 1; /* 27  */
        uint32_t RES2: 2; /* 29-28  */
        uint32_t FSCH: 2; /* 31-30    filter scheme */
    };

}CanStdFiltElement0_t;

/*
Table 90. Standard ID filter element with range scheme (FSCH = b01)
 */
typedef union{
    uint32_t dword;
    struct{
        uint32_t STD_ID_FILTER1: 11; /* 10-0   */
        uint32_t RTR_MASK: 1; /* 11  */
        uint32_t RES1: 4; /* 15-12  */
        uint32_t STD_ID_FILTER2: 11; /* 26-16   */
        uint32_t RTR_FILTER: 1; /* 27  */
        uint32_t RES2: 2; /* 29-28  */
        uint32_t FSCH: 2; /* 31-30    filter scheme 0b01*/
    };
}CanStdFiltElement1_t;

/*
Table 91. Standard ID filter element with two-filter scheme (FSCH = b10)
 */
typedef union{
    uint32_t dword;
    struct{
        uint32_t STD_ID_FILTER1: 11; /* 10-0   */
        uint32_t RTR_FILTER1: 1; /* 11  */
        uint32_t RES1: 4; /* 15-12  */
        uint32_t STD_ID_FILTER2: 11; /* 26-16   */
        uint32_t RTR_FILTER2: 1; /* 27  */
        uint32_t RES2: 2; /* 29-28  */
        uint32_t FSCH: 2; /* 31-30    filter scheme 0b10*/
    };
}CanStdFiltElement2_t;

typedef union {
    uint32_t dword;
    CanStdFiltElement0_t FilterScheme0;
    CanStdFiltElement1_t FilterScheme1;
    CanStdFiltElement2_t FilterScheme2;
}CanStdFiltElement_t;

/*
 Table 92. Extended ID filter element with filter + mask scheme (FSCH = b00)
  FSCH = b00, the filter scheme is based on mask and filter.

  (ID[n] = EXT_ID_FILTER [n]) or (EXT_ID_MASK[n]=0) for each bit n from 0 to 28
  */
typedef union {
    uint64_t qword; /**/
    struct{
        uint64_t EXT_ID_FILTER:29; /*28-0 EXT ID filter */
        uint64_t RTR_FILTER:1; /*29 RTR filter*/
        uint64_t FSCH: 2; /* 31-30   filter scheme 0b00*/

        uint64_t EXT_ID_MASK:29; /*60-32    EXT ID mask */
        uint64_t RTR_MASK:1; /*61    RTR mask*/
        uint64_t RESERVED: 2; /*63-62    Reserved*/
    };
}CanExtFiltElement0_t;


/*
Table 93. Extended ID filter element with range scheme (FSCH = b01)
If FSCH = b01, the filter scheme is based on range.
EXT ID Filter1 <= ID <= EXT ID Filter2
 */
typedef union{
    uint64_t qword;
    struct{
        uint64_t EXT_ID_FILTER2: 29; /* EXT ID Filter2*/
        uint64_t RTR_FILTER: 1; /* RTR filter*/
        uint64_t FSCH: 2; /* 31-30   FSCH filter scheme 0b01*/
        uint64_t EXT_ID_FILTER1: 29; /* EXT ID filter 1*/
        uint64_t RTR_MASK: 1; /* RTR mask*/
        uint64_t RES: 2; /* Reserved*/
    };
}CanExtFiltElement1_t;


/*
If FSCH = b10, the filters and masks are defined as shown in the following table.
the filter scheme is based on two filters without masks
(ID[n] = EXT_ID_FILTER1[n]) or (ID[n] = EXT_ID_FILTER2[n]) for each bit n from 0 to 28
 */
typedef union{
    uint64_t qword;
    struct{
        uint64_t EXT_ID_FILTER2: 29; /* EXT ID Filter2*/
        uint64_t RTR_FILTER2: 1; /* RTR Filter2*/
        uint64_t FSCH: 2; /* 31-30   FSCH filter scheme 0b10*/
        uint64_t EXT_ID_FILTER1: 29; /* EXT ID filter 1*/
        uint64_t RTR_FILTER1: 1; /* RTR Filter1*/
        uint64_t RES: 2; /* Reserved*/
    };
}CanExtFiltElement2_t;

typedef union {
    uint8_t byte[8];
    uint64_t qword;
    CanExtFiltElement0_t FilterScheme0;
    CanExtFiltElement1_t FilterScheme1;
    CanExtFiltElement2_t FilterScheme2;
}CanExtFiltElement_t;



typedef union{
    uint32_t dword;
    struct{
        uint32_t RES3: 18; /*17-0   */
        uint32_t STANDARD: 11; /*28-18   */
        uint32_t PRIO: 3; /*31-29   */
    };
    struct {
        uint32_t EXTENDED: 29; /*28-0   */
        uint32_t PRIO2: 3; /*31-29   */
    };
}CanFiFoMemId_t;

/*          Enhanced Rx (ERX) FIFO Structure
Table 107. Enhanced Rx FIFO data structure

When ERFCR[ERFEN] is set, the Enhanced Rx FIFO is enabled.
The region 2000h-204Ch contains the output of the Enhanced Rx FIFO which must be read by the CPU as a message buffer.
This output contains the oldest message that has been received but not yet read.
 */
typedef union {
    uint8_t buf[72];
    uint32_t dword[18];
    struct {
        struct {
           uint32_t TIME_STAMP: 16; /* 15-0  */
           uint32_t DLC: 4; /*19-16   */
           uint32_t RTR: 1; /*20   */
           uint32_t IDE: 1; /*21   */
           uint32_t SRR: 1; /*22   */
           uint32_t RES1: 6; /*28-23   */
           uint32_t ESI: 1; /*29   */
           uint32_t BRS: 1; /*30   */
           uint32_t EDL: 1; /*31   */
        };
        CanFiFoMemId_t ID;
        uint8_t data[64]; /*   */
        struct {
           uint32_t IDHIT: 9; /* 8-0  */
           uint32_t RES2: 23; /*31-9   */
        };
        uint32_t RES3;
    };
}CanEnhancedRxFIFOStructure_t;

#endif /* FC_CAN_ENHANCED_FIFO_TYPE_H  */
