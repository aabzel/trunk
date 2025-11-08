#include "game_pad_ps2_diag.h"

#include "game_pad_ps2.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "gpio_diag.h"
#include "array_diag.h"

const char* GamePadPs2ModeToStr(const GamePadPs2Mode_t mode){
    const char *name = "?";
    switch (mode) {
        case GAME_PAD_PS2_MODE_DISCRETE: name = "Discrete"; break;
        case GAME_PAD_PS2_MODE_CONTINUOUS: name = "Continuous"; break;
        default: name = "?"; break;
    }
    return name;
}


const char* GamePadPs2MotorToStr(const GamePadPs2Motor_t motor) {
    const char *name = "?";
    switch (motor) {
        case GAME_PAD_PS2_MOTOR_LEFT: name = "MotorLeft"; break;
        case GAME_PAD_PS2_MOTOR_RIGHT: name = "MotorRight"; break;
        default: name = "?"; break;
    }
    return name;
}

const char* GamePadPs2ConfigToStr(const GamePadPs2Config_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sSPI%u,", text, Config->spi_num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sCS:%s,", text, GpioPadToStr(Config->ChipSelect));
        //snprintf(text, sizeof(text), "%sAck:%s,", text, GpioPadToStr(Config->Ack));
    }
    return text;
}


const char* GamePadPs2DataToStr(const GamePadPs2Data_t* const Node){
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sMode:%s,", text, GamePadPs2ModeToStr(Node->mode));
        snprintf(text, sizeof(text), "%spss_rx:%u,", text, Node->pss_rx);
        snprintf(text, sizeof(text), "%spss_ry:%u,", text, Node->pss_ry);
        snprintf(text, sizeof(text), "%spss_lx:%u,", text, Node->pss_lx);
        snprintf(text, sizeof(text), "%spss_ly:%u,", text, Node->pss_ly);

        snprintf(text, sizeof(text), "%sUP:%u,", text, Node->KeyData.UP);
        snprintf(text, sizeof(text), "%sDOWN:%u,", text, Node->KeyData.DOWN);
        snprintf(text, sizeof(text), "%sLEFT:%u,", text, Node->KeyData.LEFT);
        snprintf(text, sizeof(text), "%sRIGHT:%u,", text, Node->KeyData.RIGHT);
        snprintf(text, sizeof(text), "%sSELECT:%u,", text, Node->KeyData.SELECT);
        snprintf(text, sizeof(text), "%sSTART:%u,", text, Node->KeyData.START);
        snprintf(text, sizeof(text), "%sTRIANGLE:%u,", text, Node->KeyData.TRIANGLE);
        snprintf(text, sizeof(text), "%sROUND:%u,", text, Node->KeyData.ROUND);
        snprintf(text, sizeof(text), "%sSQUARE:%u,", text, Node->KeyData.SQUARE);
        snprintf(text, sizeof(text), "%sX:%u,", text, Node->KeyData.X);

        snprintf(text, sizeof(text), "%sR1:%u,", text, Node->KeyData.R1);
        snprintf(text, sizeof(text), "%sR2:%u,", text, Node->KeyData.R2);
        snprintf(text, sizeof(text), "%sR3:%u,", text, Node->KeyData.R3);

        snprintf(text, sizeof(text), "%sL1:%u,", text, Node->KeyData.L1);
        snprintf(text, sizeof(text), "%sL2:%u,", text, Node->KeyData.L2);
        snprintf(text, sizeof(text), "%sL3:%u,", text, Node->KeyData.L3);


    }
    return text;
}

const char* GamePadPs2NodeToStr(const GamePadPs2Handle_t* const Node) {
    strcpy(text, "");
    if(Node) {

        snprintf(text, sizeof(text), "%sSTART:%u,", text, Node->RxData.Data3.START);
        snprintf(text, sizeof(text), "%sSELECT:%u,", text, Node->RxData.Data3.SELECT);
        snprintf(text, sizeof(text), "%sUP:%u,", text, Node->RxData.Data3.UP);
        snprintf(text, sizeof(text), "%sDOWN:%u,", text, Node->RxData.Data3.DOWN);
        snprintf(text, sizeof(text), "%sLEFT:%u,", text, Node->RxData.Data3.LEFT);
        snprintf(text, sizeof(text), "%sRIGHT:%u,", text, Node->RxData.Data3.RIGHT);

        snprintf(text, sizeof(text), "%sID:0x%08x,", text, Node->RxData.ID);
        snprintf(text, sizeof(text), "%sResp:0x%08x,", text, Node->RxData.resp);
        snprintf(text, sizeof(text), "%sPssRy:0x%08x,", text, Node->RxData.pss_ry);
        snprintf(text, sizeof(text), "%sPssLx:0x%08x,", text, Node->RxData.pss_lx);

        snprintf(text, sizeof(text), "%sL1:%u,", text, Node->RxData.Data4.L1);
        snprintf(text, sizeof(text), "%sL2:%u,", text, Node->RxData.Data4.L2);
        snprintf(text, sizeof(text), "%sL3:%u,", text, Node->RxData.Data3.L3);

        snprintf(text, sizeof(text), "%sR2:%u,", text, Node->RxData.Data4.R2);
        snprintf(text, sizeof(text), "%sR3:%u,", text, Node->RxData.Data3.R3);

      //  snprintf(text, sizeof(text), "%sR1:%u,", text, Node->RxData.Data4.R1);
     //   snprintf(text, sizeof(text), "%sTRIANGLE:%u,", text, Node->RxData.Data4.TRIANGLE);
       // snprintf(text, sizeof(text), "%sPssRx:0x%08x,", text, Node->RxData.pss_rx);
        //snprintf(text, sizeof(text), "%sPssLy:0x%08x,", text, Node->RxData.pss_ly);
       // snprintf(text, sizeof(text), "%sROUND:%u,", text, Node->RxData.Data4.ROUND);
      //  snprintf(text, sizeof(text), "%sX:%u,", text, Node->RxData.Data4.X);
      //  snprintf(text, sizeof(text), "%sSQUARE:%u,", text, Node->RxData.Data4.SQUARE);

        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
    }
    return text;
}


bool game_pad_ps2_diag(void) {
    bool res = false;
    return res;
}

bool game_pad_ps2_diag_one(uint8_t num){
    bool res = false;
    GamePadPs2Handle_t* Node = GamePadPs2GetNode(num);
    if(Node) {
        LOG_INFO(GAME_PAD_PS2, "TxData:%s", ArrayToStr(Node->TxData.buff,9));
        LOG_INFO(GAME_PAD_PS2, "%s", GamePadPs2NodeToStr(Node));
        res = true;
    }
    return res;
}

bool game_pad_ps2_raw_reg_diag(uint8_t num){
    bool res = false;
    return res;
}
