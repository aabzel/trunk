#include "game_pad_ps2.h"

#include "gpio_mcal.h"
#include "code_generator.h"
#include "spi_mcal.h"
#include "time_mcal.h"
#include "compiler_const.h"
#include "bit_utils.h"
#include "byte_utils.h"
#include "array.h"
#include "array_diag.h"
#include "log.h"

COMPONENT_GET_NODE(GamePadPs2, game_pad_ps2)
COMPONENT_GET_CONFIG(GamePadPs2, game_pad_ps2)

/*ISO-26262 require verify configuration*/
bool GamePadPs2IsValidConfig(const GamePadPs2Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(GAME_PAD_PS2, "GAME_PAD_PS2_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool game_pad_ps2_init_common(const GamePadPs2Config_t* const Config, GamePadPs2Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->spi_num = Config->spi_num;
            Node->ChipSelect = Config->ChipSelect;
            res = true;
        }
    }
    return res;
}


bool game_pad_ps2_init_custom(void) {
    bool res = false;
    LOG_INFO(GAME_PAD_PS2, "Version:%s", GAME_PAD_PS2_VERSION);
    return res;
}

#define PS2_SHOW_KEY_DIFF(VARIABLE,TEXT)   \
    if(Cur->VARIABLE!=Prev->VARIABLE){   \
        LOG_DEBUG(GAME_PAD_PS2, #TEXT ":%u->%u", Prev->VARIABLE, Cur->VARIABLE);   \
    }

#define PS2_SHOW_STICK_DIFF(VARIABLE,TEXT)                  \
    if(Cur->VARIABLE!=Prev->VARIABLE){                      \
        LOG_DEBUG(GAME_PAD_PS2, #TEXT ":%2u->%2u", Prev->VARIABLE, Cur->VARIABLE);   \
    }

static bool game_pad_ps2_calc_rx_diff ( const GamePadPs2Data_t* const Prev,
                                       const GamePadPs2Data_t* const Cur
                               ) {
    bool res = false;
    PS2_SHOW_STICK_DIFF(pss_lx,lx)
    PS2_SHOW_STICK_DIFF(pss_ly,ly)

    PS2_SHOW_STICK_DIFF(pss_rx,rx)
    PS2_SHOW_STICK_DIFF(pss_ry,ry)

    PS2_SHOW_KEY_DIFF(KeyData.R1,R1)
    PS2_SHOW_KEY_DIFF(KeyData.R2,R2)
    PS2_SHOW_KEY_DIFF(KeyData.R3,R3)

    PS2_SHOW_KEY_DIFF(KeyData.L1,L1)
    PS2_SHOW_KEY_DIFF(KeyData.L2,L2)
    PS2_SHOW_KEY_DIFF(KeyData.L3,L3)
    PS2_SHOW_KEY_DIFF(KeyData.UP,UP)
    PS2_SHOW_KEY_DIFF(KeyData.DOWN,DOWN)
    PS2_SHOW_KEY_DIFF(KeyData.LEFT,LEFT)
    PS2_SHOW_KEY_DIFF(KeyData.RIGHT,RIGHT)
    PS2_SHOW_KEY_DIFF(KeyData.SELECT,SELECT)
    PS2_SHOW_KEY_DIFF(KeyData.START,START)
    PS2_SHOW_KEY_DIFF(KeyData.TRIANGLE,TRIANGLE)
    PS2_SHOW_KEY_DIFF(KeyData.ROUND,ROUND)
    PS2_SHOW_KEY_DIFF(KeyData.SQUARE,SQUARE)
    PS2_SHOW_KEY_DIFF(KeyData.X,X)

    return res;
}

static bool game_pad_ps2_proc_id(const uint8_t id) {
    bool res = false;
    switch (id) {
        case GAME_PAD_PS2_ID_GREEN:
            res = true;
            break;
        case GAME_PAD_PS2_ID_RED:
            res = true;
            break;
        default: {
            res = false;
            LOG_PARN(GAME_PAD_PS2, "Undef,ID:0x%02X", id);
        }
            break;
    }

    return res;
}

static bool game_pad_ps2_move_data_ll(GamePadPs2Handle_t* const Node) {
    bool res = false;
    gpio_logic_level_set(Node->ChipSelect, GPIO_LVL_LOW);
    Node->TxData.preamble =  (GAME_PAD_PS2_PREAMBLE);
    Node->TxData.cmd =  (GAME_PAD_PS2_CMD_GET_DATA);
    res = spi_mcal_write_read(Node->spi_num, Node->TxData.buff, Node->RxData.buff, 9);
    gpio_logic_level_set(Node->ChipSelect, GPIO_LVL_HI);
    if(res){
        array_invert_bits(Node->RxData.buff, sizeof(GamePadPs2RxData_t));
        game_pad_ps2_proc_id(Node->RxData.ID);
        if ( GAME_PAD_PS2_RX_OK == Node->RxData.resp) {
        }else{
            LOG_PARN(GAME_PAD_PS2, "Undef,resp:0x%02X", Node->RxData.resp);
        }
    }

    // TODO pack to function
        Node->Data.mode= Node->RxData.ID;
        Node->Data.KeyData.TRIANGLE = Node->RxData.Data5.TRIANGLE;
        Node->Data.KeyData.ROUND = Node->RxData.Data5.ROUND;
        Node->Data.KeyData.SQUARE = Node->RxData.Data5.SQUARE;
        Node->Data.KeyData.X = Node->RxData.Data5.X;

        Node->Data.KeyData.R1 = Node->RxData.Data5.R1;
        Node->Data.KeyData.R2 = Node->RxData.Data4.R2;
        Node->Data.KeyData.R3 = Node->RxData.Data3.R3;

        Node->Data.KeyData.SELECT = Node->RxData.Data3.SELECT;
        Node->Data.KeyData.START = Node->RxData.Data3.START;

        Node->Data.KeyData.UP = Node->RxData.Data4.UP;
        Node->Data.KeyData.DOWN = Node->RxData.Data4.DOWN;

        Node->Data.KeyData.RIGHT = Node->RxData.Data4.RIGHT;
        Node->Data.KeyData.LEFT = Node->RxData.Data4.LEFT;

        Node->Data.KeyData.L1 = Node->RxData.Data4.L1;
        Node->Data.KeyData.L2 = Node->RxData.Data4.L2;
        Node->Data.KeyData.L3 = Node->RxData.Data3.L3;
        Node->Data.pss_lx = Node->RxData.pss_lx;
        Node->Data.pss_rx = Node->RxData.pss_rx;
        Node->Data.pss_ry = Node->RxData.pss_ry;
        /**/
        // Node->Data.pss_ly = Node->RxData.pss_ly;

    if(res) {
        res = game_pad_ps2_calc_rx_diff(&Node->DataPrev, &Node->Data);
        res = array_cmp(Node->RxData.buff, Node->RxDataPrev.buff,   sizeof(GamePadPs2RxData_t));
        if(!res) {
            //array_u8_print_binary(Node->RxData.buff, sizeof(GamePadPs2RxData_t));
            LOG_PARN(GAME_PAD_PS2, "PS2_%u,NewDat,[%s]", Node->num, GamePadPs2DataToStr(&Node->Data));
        }
        memcpy((void *)&Node->DataPrev,(void *)&Node->Data,sizeof(GamePadPs2RxData_t));
        memcpy((void *)Node->RxDataPrev.buff,(void *)Node->RxData.buff,sizeof(GamePadPs2RxData_t));
    }
    return res;
}
bool game_pad_ps2_write_data(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    GamePadPs2Handle_t *Node = GamePadPs2GetNode(num);
    if (Node) {
        gpio_logic_level_set(Node->ChipSelect, GPIO_LVL_LOW);
        wait_us(16);
        res = spi_mcal_write(Node->spi_num, data, size);
        wait_us(8);
        gpio_logic_level_set(Node->ChipSelect, GPIO_LVL_HI);
        wait_us(16);
    }
    return res;
}


bool game_pad_ps2_tx_set(uint8_t num, uint8_t offset, uint8_t value) {
    bool res = false;
    LOG_NOTICE(GAME_PAD_PS2, "GAME_PAD_PS2_%u,offset:%u,Val:%u", num,offset,value);
    GamePadPs2Handle_t *Node = GamePadPs2GetNode(num);
    if (Node) {
        if(offset<=8) {
            Node->TxData.buff[offset] = value;
            res = true;
        }
    }
    return res;
}

bool game_pad_ps2_vibration(uint8_t num, uint8_t motor_left, uint8_t motor_right) {
    bool res;
    GamePadPs2TxData_t TxData = { 0 };
    TxData.preamble = GAME_PAD_PS2_PREAMBLE;
    TxData.cmd = GAME_PAD_PS2_CMD_GET_DATA;
    TxData.idle1 = 0x00;
    TxData.motor_left = motor_left;
    TxData.motor_right = motor_right;
    memset(TxData.idle4, 0, 4);
    res = game_pad_ps2_write_data(num, TxData.buff, 9);
    return res;
}

bool game_pad_ps2_motor_set(uint8_t num, GamePadPs2Motor_t motor, uint8_t level) {
    bool res = false;
    LOG_NOTICE(GAME_PAD_PS2, "GAME_PAD_PS2_%u,Motor:%s,Current:%u", num,GamePadPs2MotorToStr(motor),level);
    GamePadPs2Handle_t *Node = GamePadPs2GetNode(num);
    if (Node) {
        switch (motor) {
            case GAME_PAD_PS2_MOTOR_LEFT: {
                Node->TxData.motor_left = level + 0x40;
                res = true;
            } break;
            case GAME_PAD_PS2_MOTOR_RIGHT: {
                Node->TxData.motor_right = level;
                res = true;
            } break;
            default:
                break;
        }
        res= game_pad_ps2_vibration(   num, Node->TxData.motor_left,Node->TxData.motor_right);
    }
    return res;
}

const uint8_t VibrationMode[] = {0x01, 0x4D, 0x00,  0x00, 0x01};
//const uint8_t VibrationMode[] = {0x01 , 0x4D , 0x00 , 0x00 , 0x01 , 0xFF , 0xFF , 0xFF , 0xFF};



const uint8_t ShortPoll[] = {0x01, 0x42, 0x00,  0x00, 0x00};
const uint8_t TurnOnAnalogMode[] = {0x01, 0x44, 0x00,  0x01, 0xEE, 0x00, 0x00, 0x00, 0x00};
const uint8_t EnterConfig[] = {0x01, 0x43, 0x00,  0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t ExitConfig[]  = {0x01, 0x43, 0x00,  0x00, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a};

bool game_pad_ps2_init_hw( uint8_t num) {
    bool res = false;
    LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u,InitHw", num);
    res = game_pad_ps2_write_data(  num, ShortPoll, ARRAY_SIZE(ShortPoll) );
    res = game_pad_ps2_write_data(  num, ShortPoll, ARRAY_SIZE(ShortPoll) );
    res = game_pad_ps2_write_data(  num, ShortPoll, ARRAY_SIZE(ShortPoll) );
    LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u,ShortPoll", num);

    res = game_pad_ps2_write_data(  num, EnterConfig, ARRAY_SIZE(EnterConfig) );
    LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u,EnterConfig", num);

  //  res = game_pad_ps2_write_data(  num, TurnOnAnalogMode, ARRAY_SIZE(TurnOnAnalogMode) );
  //  LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u,TurnOnAnalogMode", num);

    res = game_pad_ps2_write_data(  num, VibrationMode, ARRAY_SIZE(VibrationMode) );
    LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u,VibrationMode", num);

    res = game_pad_ps2_write_data(  num, ExitConfig, ARRAY_SIZE(ExitConfig) );
    LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u,ExitConfig", num);

    return res;
}

bool game_pad_ps2_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(GAME_PAD_PS2, "GAME_PAD_PS2%u", num);
    const GamePadPs2Config_t* Config = GamePadPs2GetConfig(num);
    if(Config) {
        res = GamePadPs2IsValidConfig(Config);
        if(res) {
#ifdef HAS_GAME_PAD_PS2_DIAG
            LOG_WARNING(GAME_PAD_PS2, "%s", GamePadPs2ConfigToStr(Config));
#endif
            GamePadPs2Handle_t* Node = GamePadPs2GetNode(num);
            if(Node) {
                res = game_pad_ps2_init_common(Config, Node);
                res = game_pad_ps2_init_hw(num);
                Node->valid = true;
                Node->init = true;
                res = true;
                log_level_get_set(GAME_PAD_PS2, LOG_LEVEL_NOTICE);
            } else {
                LOG_ERROR(GAME_PAD_PS2, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(GAME_PAD_PS2, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(GAME_PAD_PS2, "ConfigErr %u", num);
    }
    return res;
}

bool game_pad_ps2_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(GAME_PAD_PS2, "GAME_PAD_PS2_%u,Proc", num);
    GamePadPs2Handle_t* Node = GamePadPs2GetNode(num);
    if(Node) {
        res = game_pad_ps2_move_data_ll(Node);
        Node->spin++;
    }
    return res;
}

COMPONENT_INIT_PATTERT(GAME_PAD_PS2, GAME_PAD_PS2, game_pad_ps2)
COMPONENT_PROC_PATTERT(GAME_PAD_PS2, GAME_PAD_PS2, game_pad_ps2)
