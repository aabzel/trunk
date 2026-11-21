#include "ili9341_diag.h"

#include "ili9341_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "ili9341_types.h"

const char* Ili9341IdToStr( const Ili9341Id_t * const pID) {
    strcpy(text, "");
    if(pID) {
        snprintf(text, sizeof(text), "%sManInfo:0x%02x,", text, pID->man_info);
        snprintf(text, sizeof(text), "%sPanelType:0x%02x,", text, pID->panel_type);
        snprintf(text, sizeof(text), "%sDrvInfo:0x%02x,", text, pID->drv_info);
    }
    return text;
}

/*
 Serializatiors
 */
const char* Ili9341ConfigToStr(const Ili9341Config_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sSPI%u,", text, Config->spi_num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* Ili9341NodeToStr(const Ili9341Handle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool ili9341_diag_one(uint8_t num) {
    bool res = false;
    const Ili9341Config_t *Config = Ili9341GetConfig(num);
    if(Config) {
        LOG_INFO(ILI9341, "%s", Ili9341ConfigToStr(Config));
        Ili9341Handle_t *Node = Ili9341GetNode(num);
        if(Node) {
            LOG_INFO(ILI9341, "%s", Ili9341NodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool ili9341_diag(void) {
    bool res = false;
    res = ili9341_diag_one(1);
    return res;
}


bool ili9341_raw_reg_diag(uint8_t num) {
    bool res = false;
    Ili9341Handle_t *Node = Ili9341GetNode(num);
    if(Node){
        res = true;
    }
    return res;
}
