
#ifndef AD9833_CONST_H
#define AD9833_CONST_H

#define FMCLK_HZ 25000000
#define TWO_POW_28 268435456
#define TWO_POW_12 4096

typedef enum {
   AD_MCLK_ENABLED=0,
   AD_MCLK_DISABLED=1,
   AD_MCLK_UNDEF=3,
}Ad9833Mclok_t;

typedef enum {
	AD_WRITE_CTRL=0,
	AD_WRITE_FREQ0=1,
	AD_WRITE_FREQ1=2,
	AD_WRITE_PHASE0=6,
	AD_WRITE_PHASE1=7,
	AD_WRITE_UNDEF=8,
}Ad9833Write_t;

typedef enum {
	REG_NUM_0 = 0,
	REG_NUM_1 = 1,
	REG_NUM_UNDEF = 2,
}RegNum_t;

typedef enum {
	SIGNAL_FORM_SQUARE=1,
	SIGNAL_FORM_SINUSOIDAL=2,
	SIGNAL_FORM_TRIANGULAR=3,
	SIGNAL_FORM_CONST=4,
	SIGNAL_FORM_UNDEF=0,
}SignalForm_t;

typedef enum {
    DAC_POWER_DOWN=1,
    DAC_ACTIVE=0,
}Sleep12_t;


typedef enum {
	DAC_DISCONNECTED=1,
	DAC_CONNECTED=0,
}OutPutEnable_t;

typedef enum {
	MCLK_DISABLED=1,
	MCLK_ENABLED=0,
}Sleep1_t;

typedef enum {
     SIGNAL_NOT_SIN=1,
     SIGNAL_SIN=0,
}SinusRom_t;

typedef enum {
	DIV2_MSB=1,
	DIV2_MSB_2=0,
}Div2_t;

/*Table 13. Applying the Reset Function*/
typedef enum {
	RST_REG=1,
	RST_DISABLE=0,
}Reset_t;

typedef enum {
   AD_MODE_SIN=0,
   AD_MODE_TRIANGLE=1,

   AD_MODE_UNDEF=3,
}Ad9833Mode_t;

#endif /* AD9833_CONST_H */
