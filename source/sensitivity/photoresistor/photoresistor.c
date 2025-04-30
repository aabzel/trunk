#include "photoresistor.h"

#include "adc_drv.h"
#include "photoresistor_config.h"
#include "log.h"
#include "voltage_divider.h"
#include "common_diag.h"

const PhotoResistorConfig_t* PhotoResistorGetConfigNode(uint8_t num) {
    const PhotoResistorConfig_t* ChanConfNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = photo_resistor_get_cnt();
    for(i = 0; i < cnt; i++) {
        // AdcDiagConfigChannel(&PhotoResistConfig[i]);
        if(num == PhotoResistorConfig[i].num) {

                if(PhotoResistorConfig[i].valid) {
                    ChanConfNode = &PhotoResistorConfig[i];
                    break;
                }

        }
    }
    return ChanConfNode;
}

PhotoResistorHandle_t* PhotoResistorGetNode(uint8_t num) {
    PhotoResistorHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = photo_resistor_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == PhotoResistorInstance[i].num) {
                if(PhotoResistorInstance[i].valid) {
                    Node = &PhotoResistorInstance[i];
                    break;
                }
        }
    }
    return Node;
}



double photoresistor_read_om(uint8_t num) {
    double resistance = 0.0;
    const PhotoResistorConfig_t* Node=PhotoResistorGetConfigNode( num);
    if(Node) {
        double u_out_v = 0.0;
        bool res= false;
        res = adc_pad_read_voltage(Node->pad, &u_out_v);
        if(res) {
            LOG_PARN(SYS,"VoltDivOut:%f V", u_out_v);
            switch((uint8_t) Node->vd_position) {
            case VOL_DIV_GND:
                resistance = VOLT_DIV_CALC_R_GND(Node->r_vcc_om, Node->u_in_v, u_out_v);
                break;
            case VOL_DIV_VCC:
                resistance =  volt_div_calc_r_vcc(Node->r_gnd_om, Node->u_in_v,   u_out_v);
                break;
            }
        }
    }
    return resistance;
}

double resistance2lighting(double resistance, double scale ){
    double lighting = scale/ resistance;
    return lighting ;
}

bool photoresistor_proc(void){
    bool res = false;
    uint32_t i = 0;
    cli_printf(CRLF);
    uint32_t cnt = photo_resistor_get_cnt();
    for(i = 1; i <= cnt; i++) {
        PhotoResistorHandle_t* Node = PhotoResistorGetNode(i) ;
        if(Node) {
            Node->resistance = photoresistor_read_om(  i);
            Node->lighting= resistance2lighting(Node->resistance, Node->scale);
            LOG_DEBUG(PHOTORESISTOR,"Resistance:%s Om  Lighting: %f", BigVal2Str(Node->resistance),Node->lighting);
        }
    }
    return res;
}


bool photoresistor_init(void){
    bool res = false;
    uint32_t cnt = photo_resistor_get_cnt();
    LOG_WARNING(PHOTORESISTOR,"Init Cnt:%u",cnt);
    uint32_t i = 0;
    for(i = 1; i <= cnt; i++) {
        const PhotoResistorConfig_t* ConfigNode = PhotoResistorGetConfigNode(i) ;
        if(ConfigNode) {
            PhotoResistorHandle_t* Node = PhotoResistorGetNode(i) ;
            if(Node) {
                Node->scale = ConfigNode->scale;
                Node->valid = true;
                Node->u_in_v = ConfigNode->u_in_v;
                Node->r_vcc_om = ConfigNode->r_vcc_om;
                Node->r_gnd_om = ConfigNode->r_gnd_om;
                Node->pad = ConfigNode->pad;
                Node->vd_position = ConfigNode->vd_position;
                Node->num = ConfigNode->num;
                Node->lighting = 0.0;
                res = true;
            }
        }
    }
    return res;
}

double photoresistor_read_lighting(uint8_t num){
    double lighting=0.0;
    LOG_INFO(PHOTORESISTOR,"ReadLight %u", num);
       PhotoResistorHandle_t* Node = PhotoResistorGetNode(num) ;
       if (Node) {
           lighting=Node->lighting;
       }
       return lighting;
}
