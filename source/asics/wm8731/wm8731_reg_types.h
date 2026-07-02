#ifndef WM8731_REG_TYPES_H
#define WM8731_REG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

/*00*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t linvol : 5;   /*  */
        uint8_t res : 2;      /* upt Enable */
        uint8_t lin_mute : 1; /* ntrol*/
    };
} Wm8731RegLeftLineInCtrl_t;

/*01*/
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t rinvol : 5;   /*  */
        uint8_t res : 2;      /* upt Enable */
        uint8_t rin_mute : 1; /* ntrol*/
    };
} Wm8731RegRightLineInCtrl_t;

/*0x02 */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t lhpvol : 7; /* Left Channel Headphone Output Volume Control */
        uint8_t lzcen : 1;  /* Left Channel Zero Cross detect Enable */
    };
} Wm8731RegLeftHeadOutCtrl_t;

/*0x03 */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t rhpvol : 7; /* Right Channel Headphone Output Volume Control */
        uint8_t rzcen : 1;  /* Right Channel Zero Cross detect Enable */
    };
} Wm8731RegRightHeadOutCtrl_t;

/* 0x04  Analogue audio path control */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t mic_boost : 1; /* bit0 Microphone Input Level Boost        */
        uint8_t mute_mic : 1;  /* Mic Input Mute to ADC               */
        uint8_t insel : 1;     /* Microphone/Line Input Select to ADC */
        uint8_t by_pass : 1;   /* Bypass Switch                       */
        uint8_t dac_sel : 1;   /* DAC Select                          */
        uint8_t side_tone : 1; /* Side Tone Switch                    */
        uint8_t sideatt : 2;   /* Side Tone Attenuation               */
    };
} Wm8731RegAnalogAudioPathCtrl_t;

/*0x05 Digital Audio Path Control */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t adchpd : 1; /* bit0 ADC High Pass Filter Enable */
        uint8_t deemp : 2;  /* De-emphasis Control */
        uint8_t dacmute : 1;  /* DAC Soft Mute Control */
        uint8_t hpor : 1;   /* Store dc offset when High Pass Filter disabled*/
        uint8_t res : 3;
    };
} Wm8731RegDigitalAudioPathCtrl_t;

/*0x06 Power Down control */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t lineinpd : 1; /* bit0 Line Input Power Down*/
        uint8_t micpd : 1;    /* Microphone Input an Bias Power Down*/
        uint8_t adcpd : 1;    /* ADC Power Down*/
        uint8_t dacpd : 1;    /* DAC Power Down*/
        uint8_t outpd : 1;    /* Line Output Power Down*/
        uint8_t oscpd : 1;    /* Oscillator Power Down*/
        uint8_t clkoutpd : 1; /* CLKOUT power down*/
        uint8_t poweroff : 1; /* Power Off Device*/
    };
} Wm8731RegPowerDownCtrl_t;

/*0x07 Digital audio interface format */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t format : 2;  /* Audio Data Format Select   */
        uint8_t iwl : 2;     /* Input Audio Data Bit Length Select   */
        uint8_t lrp : 1;     /* DACLRC phase control (in left, right or I2S modes)   */
        uint8_t lrswap : 1;  /* DAC Left Right Clock Swap   */
        uint8_t ms : 1;      /* Master Slave Mode Control */
        uint8_t bclkinv : 1; /* Bit Clock Invert */
    };
} Wm8731RegDigitalAudioIfCtrl_t;

/*0x08 Sampling control */
typedef union {
    uint8_t reg_val;
    struct {
        uint8_t usb_normal : 1; /*bit0 Mode Select*/
        uint8_t bosr : 1;       /*Base Over-Sampling Rate*/
        uint8_t sr : 4;         /*ADC and DAC sample rate control*/
        uint8_t clkidiv2 : 1;   /*Core Clock divider select*/
        uint8_t clkodiv2 : 1;   /*CLKOUT divider select*/
    };
} Wm8731RegSamplingCtrl_t;

/*0x09 Active Control */
typedef union {
    uint8_t reg_val;
    struct {
        /* bit0 Activate Interface 1 = Active, 0 = Inactive*/
        uint8_t active : 1;
        uint8_t res : 6;
    };
} Wm8731RegActiveCtrl_t;

/*0x0F Reset control */
typedef union {
    uint8_t reg_val;
    /*Reset Register Writing 00000000 to register resets device*/
    uint8_t reset;
} Wm8731RegResetCtrl_t;

typedef union {
    uint8_t reg_val;
    Wm8731RegLeftLineInCtrl_t LeftLineInCtrl;             //1
    Wm8731RegRightLineInCtrl_t RightLineInCtrl;           //2
    Wm8731RegLeftHeadOutCtrl_t LeftHeadOutCtrl;           //3
    Wm8731RegRightHeadOutCtrl_t RightHeadOutCtrl;         //4
    Wm8731RegAnalogAudioPathCtrl_t AnalogAudioPathCtrl;   //5
    Wm8731RegDigitalAudioPathCtrl_t DigitalAudioPathCtrl; //6
    Wm8731RegPowerDownCtrl_t PowerDownCtrl;               //7
    Wm8731RegDigitalAudioIfCtrl_t DigitalAudioIfCtrl;     //8
    Wm8731RegSamplingCtrl_t SamplingCtrl;                 //9
    Wm8731RegActiveCtrl_t ActiveCtrl;                     //10
    Wm8731RegResetCtrl_t ResetCtrl;                       //11
} Wm8731RegGeneral_t;

#endif /* WM8731_REG_TYPES_H */
