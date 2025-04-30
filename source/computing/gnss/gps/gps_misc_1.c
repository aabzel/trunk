#include "gps_misc_1.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "array_diag.h"
#include "num_to_str.h"
#include "bit_utils.h"
#include "file_pc.h"
#include "gnss_drv.h"
#include "gps.h"
#include "log.h"
#include "utils_math.h"

// Code is taken from https://github.com/taroz/GNSS-SDRLIB
/* C/A code (IS-GPS-200) -----------------------------------------------------*/
void gps_generate_prn(uint8_t* dest, int prn) {
    const static int16_t delay[] = {
        /* G2 delay (chips) */
        5,    6,   7,    8,   17,   18,  139,  140,  141, 251, /*   1- 10 */
        252,  254, 255,  256, 257,  258, 469,  470,  471, 472, /*  11- 20 */
        473,  474, 509,  512, 513,  514, 515,  516,  859, 860, /*  21- 30 */
        861,  862, 863,  950, 947,  948, 950,  67,   103, 91,  /*  31- 40 */
        19,   679, 225,  625, 946,  638, 161,  1001, 554, 280, /*  41- 50 */
        710,  709, 775,  864, 558,  220, 397,  55,   898, 759, /*  51- 60 */
        367,  299, 1018, 729, 695,  780, 801,  788,  732, 34,  /*  61- 70 */
        320,  327, 389,  407, 525,  405, 221,  761,  260, 326, /*  71- 80 */
        955,  653, 699,  422, 188,  438, 959,  539,  879, 677, /*  81- 90 */
        586,  153, 792,  814, 446,  264, 1015, 278,  536, 819, /*  91-100 */
        156,  957, 159,  712, 885,  461, 248,  713,  126, 807, /* 101-110 */
        279,  122, 197,  693, 632,  771, 467,  647,  203, 145, /* 111-120 */
        175,  52,  21,   237, 235,  886, 657,  634,  762, 355, /* 121-130 */
        1012, 176, 603,  130, 359,  595, 68,   386,  797, 456, /* 131-140 */
        499,  883, 307,  127, 211,  121, 118,  163,  628, 853, /* 141-150 */
        484,  289, 811,  202, 1021, 463, 568,  904,  670, 230, /* 151-160 */
        911,  684, 309,  644, 932,  12,  314,  891,  212, 185, /* 161-170 */
        675,  503, 150,  395, 345,  846, 798,  992,  357, 995, /* 171-180 */
        877,  112, 144,  476, 193,  109, 445,  291,  87,  399, /* 181-190 */
        292,  901, 339,  208, 711,  189, 263,  537,  663, 942, /* 191-200 */
        173,  900, 30,   500, 935,  556, 373,  85,   652, 310  /* 201-210 */
    };
    int8_t G1[PRN_LENGTH], G2[PRN_LENGTH], R1[10], R2[10], C1, C2;
    int i, j;

    if(prn < 1)
        return;

    for(i = 0; i < 10; i++)
        R1[i] = R2[i] = -1;

    for(i = 0; i < PRN_LENGTH; i++) {
        G1[i] = R1[9];
        G2[i] = R2[9];
        C1 = R1[2] * R1[9];
        C2 = R2[1] * R2[2] * R2[5] * R2[7] * R2[8] * R2[9];
        for(j = 9; j > 0; j--) {
            R1[j] = R1[j - 1];
            R2[j] = R2[j - 1];
        }
        R1[0] = C1;
        R2[0] = C2;
    }
    for(i = 0, j = PRN_LENGTH - delay[prn - 1]; i < PRN_LENGTH; i++, j++) {
        short tmp_val = -G1[i] * G2[j % PRN_LENGTH];
        dest[i] = (tmp_val < 0) ? 0 : 1;
    }

    return;
}

/// Read block, size - in bytes
bool gps_reader_read_block_ll(GpsHandle_t* const Node, uint8_t* const data, size_t size) {
    bool res = false;
    if(Node->FilePtr) {
        if(size) {
            if(data) {
                size_t nread = fread(data, 1, size, Node->FilePtr);
                if(nread == size) {
                    Node->bytes_read += nread;
                    res = true;
                }else{
                	LOG_ERROR(GPS,"ReadErr");
                }
            }else{
            	LOG_ERROR(GPS,"DataErr");
            }
        }else{
        	LOG_ERROR(GPS,"SizeErr");
        }
    }else{
    	LOG_ERROR(GPS,"FileErr");
    }
    return res;
}

bool file_read_i8_ll(FILE* FilePtr, int8_t* const sample, size_t size) {
    bool res = false;
    if(FilePtr) {
        if(size) {
            if(sample) {
                size_t nread = fread(sample, 1, size, FilePtr);
                if(nread == size) {
                    res = true;
                }
            }
        }
    }
    return res;
}

/* set 4 LSB bits
Byte:0x00=0b0000_0000->Rev:0x00=0b0000_0000
Byte:0x01=0b0000_0001->Rev:0x00=0b0000_0000
Byte:0x02=0b0000_0010->Rev:0x00=0b0000_0000
Byte:0x03=0b0000_0011->Rev:0x00=0b0000_0000
Byte:0x04=0b0000_0100->Rev:0x00=0b0000_0000
Byte:0x05=0b0000_0101->Rev:0x00=0b0000_0000
Byte:0x06=0b0000_0110->Rev:0x00=0b0000_0000
Byte:0x07=0b0000_0111->Rev:0x00=0b0000_0000
Byte:0x08=0b0000_1000->Rev:0x00=0b0000_0000
Byte:0x09=0b0000_1001->Rev:0x00=0b0000_0000
Byte:0x0a=0b0000_1010->Rev:0x00=0b0000_0000
Byte:0x0b=0b0000_1011->Rev:0x00=0b0000_0000
Byte:0x0c=0b0000_1100->Rev:0x00=0b0000_0000
Byte:0x0d=0b0000_1101->Rev:0x00=0b0000_0000
Byte:0x0e=0b0000_1110->Rev:0x00=0b0000_0000
Byte:0x0f=0b0000_1111->Rev:0x00=0b0000_0000
Byte:0x10=0b0001_0000->Rev:0x08=0b0000_1000
Byte:0x11=0b0001_0001->Rev:0x08=0b0000_1000
Byte:0x12=0b0001_0010->Rev:0x08=0b0000_1000
Byte:0x13=0b0001_0011->Rev:0x08=0b0000_1000
Byte:0x14=0b0001_0100->Rev:0x08=0b0000_1000
Byte:0x15=0b0001_0101->Rev:0x08=0b0000_1000
Byte:0x16=0b0001_0110->Rev:0x08=0b0000_1000
Byte:0x17=0b0001_0111->Rev:0x08=0b0000_1000
Byte:0x18=0b0001_1000->Rev:0x08=0b0000_1000
Byte:0x19=0b0001_1001->Rev:0x08=0b0000_1000
Byte:0x1a=0b0001_1010->Rev:0x08=0b0000_1000
Byte:0x1b=0b0001_1011->Rev:0x08=0b0000_1000
Byte:0x1c=0b0001_1100->Rev:0x08=0b0000_1000
Byte:0x1d=0b0001_1101->Rev:0x08=0b0000_1000
Byte:0x1e=0b0001_1110->Rev:0x08=0b0000_1000
Byte:0x1f=0b0001_1111->Rev:0x08=0b0000_1000
Byte:0x20=0b0010_0000->Rev:0x04=0b0000_0100
Byte:0x21=0b0010_0001->Rev:0x04=0b0000_0100
Byte:0x22=0b0010_0010->Rev:0x04=0b0000_0100
Byte:0x23=0b0010_0011->Rev:0x04=0b0000_0100
Byte:0x24=0b0010_0100->Rev:0x04=0b0000_0100
Byte:0x25=0b0010_0101->Rev:0x04=0b0000_0100
Byte:0x26=0b0010_0110->Rev:0x04=0b0000_0100
Byte:0x27=0b0010_0111->Rev:0x04=0b0000_0100
Byte:0x28=0b0010_1000->Rev:0x04=0b0000_0100
Byte:0x29=0b0010_1001->Rev:0x04=0b0000_0100
Byte:0x2a=0b0010_1010->Rev:0x04=0b0000_0100
Byte:0x2b=0b0010_1011->Rev:0x04=0b0000_0100
Byte:0x2c=0b0010_1100->Rev:0x04=0b0000_0100
Byte:0x2d=0b0010_1101->Rev:0x04=0b0000_0100
Byte:0x2e=0b0010_1110->Rev:0x04=0b0000_0100
Byte:0x2f=0b0010_1111->Rev:0x04=0b0000_0100
Byte:0x30=0b0011_0000->Rev:0x0c=0b0000_1100
Byte:0x31=0b0011_0001->Rev:0x0c=0b0000_1100
Byte:0x32=0b0011_0010->Rev:0x0c=0b0000_1100
Byte:0x33=0b0011_0011->Rev:0x0c=0b0000_1100
Byte:0x34=0b0011_0100->Rev:0x0c=0b0000_1100
Byte:0x35=0b0011_0101->Rev:0x0c=0b0000_1100
Byte:0x36=0b0011_0110->Rev:0x0c=0b0000_1100
Byte:0x37=0b0011_0111->Rev:0x0c=0b0000_1100
Byte:0x38=0b0011_1000->Rev:0x0c=0b0000_1100
Byte:0x39=0b0011_1001->Rev:0x0c=0b0000_1100
Byte:0x3a=0b0011_1010->Rev:0x0c=0b0000_1100
Byte:0x3b=0b0011_1011->Rev:0x0c=0b0000_1100
Byte:0x3c=0b0011_1100->Rev:0x0c=0b0000_1100
Byte:0x3d=0b0011_1101->Rev:0x0c=0b0000_1100
Byte:0x3e=0b0011_1110->Rev:0x0c=0b0000_1100
Byte:0x3f=0b0011_1111->Rev:0x0c=0b0000_1100
Byte:0x40=0b0100_0000->Rev:0x02=0b0000_0010
Byte:0x41=0b0100_0001->Rev:0x02=0b0000_0010
Byte:0x42=0b0100_0010->Rev:0x02=0b0000_0010
Byte:0x43=0b0100_0011->Rev:0x02=0b0000_0010
Byte:0x44=0b0100_0100->Rev:0x02=0b0000_0010
Byte:0x45=0b0100_0101->Rev:0x02=0b0000_0010
Byte:0x46=0b0100_0110->Rev:0x02=0b0000_0010
Byte:0x47=0b0100_0111->Rev:0x02=0b0000_0010
Byte:0x48=0b0100_1000->Rev:0x02=0b0000_0010
Byte:0x49=0b0100_1001->Rev:0x02=0b0000_0010
Byte:0x4a=0b0100_1010->Rev:0x02=0b0000_0010
Byte:0x4b=0b0100_1011->Rev:0x02=0b0000_0010
Byte:0x4c=0b0100_1100->Rev:0x02=0b0000_0010
Byte:0x4d=0b0100_1101->Rev:0x02=0b0000_0010
Byte:0x4e=0b0100_1110->Rev:0x02=0b0000_0010
Byte:0x4f=0b0100_1111->Rev:0x02=0b0000_0010
Byte:0x50=0b0101_0000->Rev:0x0a=0b0000_1010
Byte:0x51=0b0101_0001->Rev:0x0a=0b0000_1010
Byte:0x52=0b0101_0010->Rev:0x0a=0b0000_1010
Byte:0x53=0b0101_0011->Rev:0x0a=0b0000_1010
Byte:0x54=0b0101_0100->Rev:0x0a=0b0000_1010
Byte:0x55=0b0101_0101->Rev:0x0a=0b0000_1010
Byte:0x56=0b0101_0110->Rev:0x0a=0b0000_1010
Byte:0x57=0b0101_0111->Rev:0x0a=0b0000_1010
Byte:0x58=0b0101_1000->Rev:0x0a=0b0000_1010
Byte:0x59=0b0101_1001->Rev:0x0a=0b0000_1010
Byte:0x5a=0b0101_1010->Rev:0x0a=0b0000_1010
Byte:0x5b=0b0101_1011->Rev:0x0a=0b0000_1010
Byte:0x5c=0b0101_1100->Rev:0x0a=0b0000_1010
Byte:0x5d=0b0101_1101->Rev:0x0a=0b0000_1010
Byte:0x5e=0b0101_1110->Rev:0x0a=0b0000_1010
Byte:0x5f=0b0101_1111->Rev:0x0a=0b0000_1010
Byte:0x60=0b0110_0000->Rev:0x06=0b0000_0110
Byte:0x61=0b0110_0001->Rev:0x06=0b0000_0110
Byte:0x62=0b0110_0010->Rev:0x06=0b0000_0110
Byte:0x63=0b0110_0011->Rev:0x06=0b0000_0110
Byte:0x64=0b0110_0100->Rev:0x06=0b0000_0110
Byte:0x65=0b0110_0101->Rev:0x06=0b0000_0110
Byte:0x66=0b0110_0110->Rev:0x06=0b0000_0110
Byte:0x67=0b0110_0111->Rev:0x06=0b0000_0110
Byte:0x68=0b0110_1000->Rev:0x06=0b0000_0110
Byte:0x69=0b0110_1001->Rev:0x06=0b0000_0110
Byte:0x6a=0b0110_1010->Rev:0x06=0b0000_0110
Byte:0x6b=0b0110_1011->Rev:0x06=0b0000_0110
Byte:0x6c=0b0110_1100->Rev:0x06=0b0000_0110
Byte:0x6d=0b0110_1101->Rev:0x06=0b0000_0110
Byte:0x6e=0b0110_1110->Rev:0x06=0b0000_0110
Byte:0x6f=0b0110_1111->Rev:0x06=0b0000_0110
Byte:0x70=0b0111_0000->Rev:0x0e=0b0000_1110
Byte:0x71=0b0111_0001->Rev:0x0e=0b0000_1110
Byte:0x72=0b0111_0010->Rev:0x0e=0b0000_1110
Byte:0x73=0b0111_0011->Rev:0x0e=0b0000_1110
Byte:0x74=0b0111_0100->Rev:0x0e=0b0000_1110
Byte:0x75=0b0111_0101->Rev:0x0e=0b0000_1110
Byte:0x76=0b0111_0110->Rev:0x0e=0b0000_1110
Byte:0x77=0b0111_0111->Rev:0x0e=0b0000_1110
Byte:0x78=0b0111_1000->Rev:0x0e=0b0000_1110
Byte:0x79=0b0111_1001->Rev:0x0e=0b0000_1110
Byte:0x7a=0b0111_1010->Rev:0x0e=0b0000_1110
Byte:0x7b=0b0111_1011->Rev:0x0e=0b0000_1110
Byte:0x7c=0b0111_1100->Rev:0x0e=0b0000_1110
Byte:0x7d=0b0111_1101->Rev:0x0e=0b0000_1110
Byte:0x7e=0b0111_1110->Rev:0x0e=0b0000_1110
Byte:0x7f=0b0111_1111->Rev:0x0e=0b0000_1110
Byte:0x80=0b1000_0000->Rev:0x01=0b0000_0001
Byte:0x81=0b1000_0001->Rev:0x01=0b0000_0001
Byte:0x82=0b1000_0010->Rev:0x01=0b0000_0001
Byte:0x83=0b1000_0011->Rev:0x01=0b0000_0001
Byte:0x84=0b1000_0100->Rev:0x01=0b0000_0001
Byte:0x85=0b1000_0101->Rev:0x01=0b0000_0001
Byte:0x86=0b1000_0110->Rev:0x01=0b0000_0001
Byte:0x87=0b1000_0111->Rev:0x01=0b0000_0001
Byte:0x88=0b1000_1000->Rev:0x01=0b0000_0001
Byte:0x89=0b1000_1001->Rev:0x01=0b0000_0001
Byte:0x8a=0b1000_1010->Rev:0x01=0b0000_0001
Byte:0x8b=0b1000_1011->Rev:0x01=0b0000_0001
Byte:0x8c=0b1000_1100->Rev:0x01=0b0000_0001
Byte:0x8d=0b1000_1101->Rev:0x01=0b0000_0001
Byte:0x8e=0b1000_1110->Rev:0x01=0b0000_0001
Byte:0x8f=0b1000_1111->Rev:0x01=0b0000_0001
Byte:0x90=0b1001_0000->Rev:0x09=0b0000_1001
Byte:0x91=0b1001_0001->Rev:0x09=0b0000_1001
Byte:0x92=0b1001_0010->Rev:0x09=0b0000_1001
Byte:0x93=0b1001_0011->Rev:0x09=0b0000_1001
Byte:0x94=0b1001_0100->Rev:0x09=0b0000_1001
Byte:0x95=0b1001_0101->Rev:0x09=0b0000_1001
Byte:0x96=0b1001_0110->Rev:0x09=0b0000_1001
Byte:0x97=0b1001_0111->Rev:0x09=0b0000_1001
Byte:0x98=0b1001_1000->Rev:0x09=0b0000_1001
Byte:0x99=0b1001_1001->Rev:0x09=0b0000_1001
Byte:0x9a=0b1001_1010->Rev:0x09=0b0000_1001
Byte:0x9b=0b1001_1011->Rev:0x09=0b0000_1001
Byte:0x9c=0b1001_1100->Rev:0x09=0b0000_1001
Byte:0x9d=0b1001_1101->Rev:0x09=0b0000_1001
Byte:0x9e=0b1001_1110->Rev:0x09=0b0000_1001
Byte:0x9f=0b1001_1111->Rev:0x09=0b0000_1001
Byte:0xa0=0b1010_0000->Rev:0x05=0b0000_0101
Byte:0xa1=0b1010_0001->Rev:0x05=0b0000_0101
Byte:0xa2=0b1010_0010->Rev:0x05=0b0000_0101
Byte:0xa3=0b1010_0011->Rev:0x05=0b0000_0101
Byte:0xa4=0b1010_0100->Rev:0x05=0b0000_0101
Byte:0xa5=0b1010_0101->Rev:0x05=0b0000_0101
Byte:0xa6=0b1010_0110->Rev:0x05=0b0000_0101
Byte:0xa7=0b1010_0111->Rev:0x05=0b0000_0101
Byte:0xa8=0b1010_1000->Rev:0x05=0b0000_0101
Byte:0xa9=0b1010_1001->Rev:0x05=0b0000_0101
Byte:0xaa=0b1010_1010->Rev:0x05=0b0000_0101
Byte:0xab=0b1010_1011->Rev:0x05=0b0000_0101
Byte:0xac=0b1010_1100->Rev:0x05=0b0000_0101
Byte:0xad=0b1010_1101->Rev:0x05=0b0000_0101
Byte:0xae=0b1010_1110->Rev:0x05=0b0000_0101
Byte:0xaf=0b1010_1111->Rev:0x05=0b0000_0101
Byte:0xb0=0b1011_0000->Rev:0x0d=0b0000_1101
Byte:0xb1=0b1011_0001->Rev:0x0d=0b0000_1101
Byte:0xb2=0b1011_0010->Rev:0x0d=0b0000_1101
Byte:0xb3=0b1011_0011->Rev:0x0d=0b0000_1101
Byte:0xb4=0b1011_0100->Rev:0x0d=0b0000_1101
Byte:0xb5=0b1011_0101->Rev:0x0d=0b0000_1101
Byte:0xb6=0b1011_0110->Rev:0x0d=0b0000_1101
Byte:0xb7=0b1011_0111->Rev:0x0d=0b0000_1101
Byte:0xb8=0b1011_1000->Rev:0x0d=0b0000_1101
Byte:0xb9=0b1011_1001->Rev:0x0d=0b0000_1101
Byte:0xba=0b1011_1010->Rev:0x0d=0b0000_1101
Byte:0xbb=0b1011_1011->Rev:0x0d=0b0000_1101
Byte:0xbc=0b1011_1100->Rev:0x0d=0b0000_1101
Byte:0xbd=0b1011_1101->Rev:0x0d=0b0000_1101
Byte:0xbe=0b1011_1110->Rev:0x0d=0b0000_1101
Byte:0xbf=0b1011_1111->Rev:0x0d=0b0000_1101
Byte:0xc0=0b1100_0000->Rev:0x03=0b0000_0011
Byte:0xc1=0b1100_0001->Rev:0x03=0b0000_0011
Byte:0xc2=0b1100_0010->Rev:0x03=0b0000_0011
Byte:0xc3=0b1100_0011->Rev:0x03=0b0000_0011
Byte:0xc4=0b1100_0100->Rev:0x03=0b0000_0011
Byte:0xc5=0b1100_0101->Rev:0x03=0b0000_0011
Byte:0xc6=0b1100_0110->Rev:0x03=0b0000_0011
Byte:0xc7=0b1100_0111->Rev:0x03=0b0000_0011
Byte:0xc8=0b1100_1000->Rev:0x03=0b0000_0011
Byte:0xc9=0b1100_1001->Rev:0x03=0b0000_0011
Byte:0xca=0b1100_1010->Rev:0x03=0b0000_0011
Byte:0xcb=0b1100_1011->Rev:0x03=0b0000_0011
Byte:0xcc=0b1100_1100->Rev:0x03=0b0000_0011
Byte:0xcd=0b1100_1101->Rev:0x03=0b0000_0011
Byte:0xce=0b1100_1110->Rev:0x03=0b0000_0011
Byte:0xcf=0b1100_1111->Rev:0x03=0b0000_0011
Byte:0xd0=0b1101_0000->Rev:0x0b=0b0000_1011
Byte:0xd1=0b1101_0001->Rev:0x0b=0b0000_1011
Byte:0xd2=0b1101_0010->Rev:0x0b=0b0000_1011
Byte:0xd3=0b1101_0011->Rev:0x0b=0b0000_1011
Byte:0xd4=0b1101_0100->Rev:0x0b=0b0000_1011
Byte:0xd5=0b1101_0101->Rev:0x0b=0b0000_1011
Byte:0xd6=0b1101_0110->Rev:0x0b=0b0000_1011
Byte:0xd7=0b1101_0111->Rev:0x0b=0b0000_1011
Byte:0xd8=0b1101_1000->Rev:0x0b=0b0000_1011
Byte:0xd9=0b1101_1001->Rev:0x0b=0b0000_1011
Byte:0xda=0b1101_1010->Rev:0x0b=0b0000_1011
Byte:0xdb=0b1101_1011->Rev:0x0b=0b0000_1011
Byte:0xdc=0b1101_1100->Rev:0x0b=0b0000_1011
Byte:0xdd=0b1101_1101->Rev:0x0b=0b0000_1011
Byte:0xde=0b1101_1110->Rev:0x0b=0b0000_1011
Byte:0xdf=0b1101_1111->Rev:0x0b=0b0000_1011
Byte:0xe0=0b1110_0000->Rev:0x07=0b0000_0111
Byte:0xe1=0b1110_0001->Rev:0x07=0b0000_0111
Byte:0xe2=0b1110_0010->Rev:0x07=0b0000_0111
Byte:0xe3=0b1110_0011->Rev:0x07=0b0000_0111
Byte:0xe4=0b1110_0100->Rev:0x07=0b0000_0111
Byte:0xe5=0b1110_0101->Rev:0x07=0b0000_0111
Byte:0xe6=0b1110_0110->Rev:0x07=0b0000_0111
Byte:0xe7=0b1110_0111->Rev:0x07=0b0000_0111
Byte:0xe8=0b1110_1000->Rev:0x07=0b0000_0111
Byte:0xe9=0b1110_1001->Rev:0x07=0b0000_0111
Byte:0xea=0b1110_1010->Rev:0x07=0b0000_0111
Byte:0xeb=0b1110_1011->Rev:0x07=0b0000_0111
Byte:0xec=0b1110_1100->Rev:0x07=0b0000_0111
Byte:0xed=0b1110_1101->Rev:0x07=0b0000_0111
Byte:0xee=0b1110_1110->Rev:0x07=0b0000_0111
Byte:0xef=0b1110_1111->Rev:0x07=0b0000_0111
Byte:0xf0=0b1111_0000->Rev:0x0f=0b0000_1111
Byte:0xf1=0b1111_0001->Rev:0x0f=0b0000_1111
Byte:0xf2=0b1111_0010->Rev:0x0f=0b0000_1111
Byte:0xf3=0b1111_0011->Rev:0x0f=0b0000_1111
Byte:0xf4=0b1111_0100->Rev:0x0f=0b0000_1111
Byte:0xf5=0b1111_0101->Rev:0x0f=0b0000_1111
Byte:0xf6=0b1111_0110->Rev:0x0f=0b0000_1111
Byte:0xf7=0b1111_0111->Rev:0x0f=0b0000_1111
Byte:0xf8=0b1111_1000->Rev:0x0f=0b0000_1111
Byte:0xf9=0b1111_1001->Rev:0x0f=0b0000_1111
Byte:0xfa=0b1111_1010->Rev:0x0f=0b0000_1111
Byte:0xfb=0b1111_1011->Rev:0x0f=0b0000_1111
Byte:0xfc=0b1111_1100->Rev:0x0f=0b0000_1111
Byte:0xfd=0b1111_1101->Rev:0x0f=0b0000_1111
Byte:0xfe=0b1111_1110->Rev:0x0f=0b0000_1111
Byte:0xff=0b1111_1111->Rev:0x0f=0b0000_1111
  */
uint8_t reverse_bits(uint8_t data) {
    uint8_t res = 0;
    //cli_printf(CRLF);
    //LOG_INFO(GPS, "Byte:0x%02x=0b%s", data, utoa_bin8(data));
    for(uint8_t i = 0; i < 4; i++) {
        if(data & 0x80) {
            res |= (1 << i);
        }
        data = data << 1;
    }

    //LOG_INFO(GPS, " Rev:0x%02x=0b%s", res, utoa_bin8(res));

    return res;
}

/*
 */
bool data_reader_read_unpack_ll(GpsHandle_t* const Node, uint8_t* const data, uint16_t samples_cnt) {
    bool res = false;
    LOG_INFO(GPS, "Read:%u samples", samples_cnt);
    // 1 byte packed - 4 samples; 1 sample - 2 bit
    uint16_t bytes_to_read = samples_cnt / 4; // packed bytes - 4Kbyte
    if(bytes_to_read <= PACKED_BUF_SIZE) {
        LOG_INFO(GPS, "BytesToRead:%u byte", bytes_to_read);
        res = gps_reader_read_block_ll(Node, Node->packed_data_buf, bytes_to_read);
        if(res) {
            res = false;
            memset(data, 0, samples_cnt / 8);

            uint16_t dst_cnt = 0;
            for(uint16_t i = 0; i < bytes_to_read; i++) {
                // analyse packeed bytes
                dst_cnt = i / 2;
                uint8_t packed_byte = Node->packed_data_buf[i];
                uint8_t tmp = reverse_bits(packed_byte); // 4bits
                if((i & 1) == 0) {                       /*if first bit zero (is odd [devided by 2])*/
                    data[dst_cnt] |= tmp;
                } else {
                    data[dst_cnt] |= tmp << 4;
                }
                LOG_INFO(GPS, "ProcSample [%u]=0x%x", dst_cnt, data[dst_cnt]);
            }
        }
    }

    return 1;
}

int8_t GpsSampleToInt(uint8_t sample_code) {
    int8_t sample = 0;
    switch(sample_code) {
    case 0:   /*1in FPGA*/
        sample = 1;
        break; /*00*/
    case 1:
        sample = 3;
        break; /*01*/
    case 2:
        sample = -1;
        break; /*10*/
    case 3:
        sample = -3;
        break; /*11*/
    default:
        LOG_ERROR(GPS, "UndefCode 0b%s->Sample %d ", utoa_bin8(sample_code), sample);
        break;
    }
    LOG_PARN(GPS, "code 0b%s->Sample %d ", utoa_bin8(sample_code), sample);
    return sample;
}

uint8_t GetPackedSampleCode(uint8_t packet_byte, uint8_t sample_index) {
    uint8_t sample_code = 0;
    GnssFpgaPackByte_t PackByte;
    PackByte.byte = packet_byte;
    switch(sample_index) {
    case 0: {
        if(PackByte.sig0) {
            SET_BIT_NUM(sample_code, 1);
        }
        if(PackByte.mag0) {
            SET_BIT_NUM(sample_code, 0);
        }
    } break;
    case 1: {
        if(PackByte.sig1) {
            SET_BIT_NUM(sample_code, 1);
        }
        if(PackByte.mag1) {
            SET_BIT_NUM(sample_code, 0);
        }

    } break;
    case 2: {
        if(PackByte.sig2) {
            SET_BIT_NUM(sample_code, 1);
        }
        if(PackByte.mag2) {
            SET_BIT_NUM(sample_code, 0);
        }

    } break;
    case 3: {
        if(PackByte.sig3) {
            SET_BIT_NUM(sample_code, 1);
        }
        if(PackByte.mag3) {
            SET_BIT_NUM(sample_code, 0);
        }
    } break;
    default:
        LOG_ERROR(GPS, "IndexErr %d", sample_index);
        break;
    }
    LOG_PARN(GPS, "Sample, Code:%u->Val:%d", sample_code, GpsSampleToInt(sample_code));
    return sample_code;
}

bool data_reader_read_samples_ll(GpsHandle_t* const Node, int8_t* const samples, uint16_t samples_cnt) {
    bool res = false;
    LOG_DEBUG(GPS, "Read:%u samples", samples_cnt);
    // 1 byte packed - 4 samples; 1 sample - 2 bit
    uint16_t bytes_to_read = samples_cnt / 4;
    if(bytes_to_read <= PACKED_BUF_SIZE) {
        LOG_DEBUG(GPS, "BytesToRead:%u byte", bytes_to_read);
        res = gps_reader_read_block_ll(Node, Node->packed_data_buf, bytes_to_read);
        if(res) {
            res = false;
            U16_bit_t packet_word;
            packet_word.u16 = 0;
            int32_t sam_ind = 0;
            int32_t b = 0;
            for(uint32_t w = 0; w < (bytes_to_read/2); w++) {
            	packet_word.u8[0]=Node->packed_data_buf[w*2+1];
            	packet_word.u8[1]=Node->packed_data_buf[w*2];

            	for(b=0;b<2;b++){
                    //packet_byte = Node->packed_data_buf[i];
                    LOG_DEBUG(GPS, "ProcByte [%d]=0x%x=0b%s", w, packet_word.u8[b], utoa_bin8(packet_word.u8[b]));
                    // analyse packeed bytes

                    int32_t sub_s = 0;
                    for(sub_s = 0; sub_s < 4; sub_s++) {
                        sam_ind = w * 8 + b*4 + sub_s;
                        uint8_t sample_code = GetPackedSampleCode(packet_word.u8[b], sub_s);
                        samples[sam_ind] = GpsSampleToInt(sample_code);
                        LOG_DEBUG(GPS, "[%d/%d/%d]=Code:%u->Sample:%d", sam_ind,b, sub_s, sample_code, samples[sam_ind]);
                    }

            	}
            }
        }
    }

    return 1;
}


#define SAMPLE_PROC_CNT (4 * 2048)
bool gps_post_proc(uint8_t num, const char* const file_name) {
    bool res = false;
    if(file_name) {
        LOG_INFO(GPS, "PostProc File:[%s]", file_name);
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            Node->size_bytes = file_pc_get_size(file_name);
            Node->sample_cnt = Node->size_bytes * 4;
            Node->duration_s = (double)Node->sample_cnt / Node->adc_sample_rate_hz;
            LOG_INFO(GPS, "OpenOkFile:[%s],Size:%d bytes,Samples:%u,Duration:%f s", file_name, Node->size_bytes,
                     Node->sample_cnt, Node->duration_s);
            Node->FilePtr = fopen(file_name, "rb");
            if(Node->FilePtr) {
                LOG_INFO(GPS, "OpenOkFile:[%s]", file_name);

                uint32_t s = 0;
                int8_t sample_data[SAMPLE_PROC_CNT] = {0};
                for(s = 0; s < Node->sample_cnt;) {
                    res = data_reader_read_samples_ll(Node, sample_data, sizeof(sample_data));
                    if(res) {
                        // array_i8_print( sample_data, sizeof(sample_data));
                        res = file_pc_save_array("adc_sample_i8_2.bin", sample_data, SAMPLE_PROC_CNT);
                        print_progress(s, Node->sample_cnt);
                    }
                    s += SAMPLE_PROC_CNT;
                }
                fclose(Node->FilePtr);
                cli_printf(CRLF);
            } else {
                LOG_ERROR(GPS, "OpenErrFile:[%s]", file_name);
                res = false;
            }
        } else {
            res = false;
        }
    } else {
        res = false;
    }
    return res;
}

bool gps_proc_sample(uint8_t num, const char* const file_name) {
    bool res = false;
    if(file_name) {
        LOG_INFO(GPS, "PostProc File:[%s]", file_name);
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            Node->FilePtr = fopen(file_name, "rb");
            if(Node->FilePtr) {
                LOG_INFO(GPS, "OpenOkFile:[%s]", file_name);
                Node->size_bytes = file_pc_get_size(file_name);
                Node->sample_cnt = Node->size_bytes;
                Node->duration_s = (double)Node->sample_cnt / Node->adc_sample_rate_hz;
                LOG_INFO(GPS, "OpenOkFile:[%s],Size:%d bytes,Samples:%u,Duration:%f s", file_name, Node->size_bytes,
                         Node->sample_cnt, Node->duration_s);
                int8_t sample_data[2 * ONE_PRN_SAMPLE_CNT] = {0};
                res = file_read_i8_ll(Node->FilePtr, sample_data, sizeof(sample_data));
                if(res) {
                    // array_i8_print( sample_data, sizeof(sample_data));
                    res = gps_proc_data(Node, sample_data, sizeof(sample_data));
                }

                fclose(Node->FilePtr);
                cli_printf(CRLF);
            } else {
                LOG_ERROR(GPS, "OpenErrFile:[%s]", file_name);
                res = false;
            }
        }
    }
    return res;
}
