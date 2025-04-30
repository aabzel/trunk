#include "clock_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "artery_at32f4xx.h"
#include "clock.h"
#include "clock_types.h"
#include "common_diag.h"
#include "log.h"
#include "log_utils.h"

#ifdef HAS_STRING
#include "str_utils.h"
#endif

bool print_conditional(char* key_word1, char* key_word2, char* bus, char* module, bool on_off) {
    bool res = false;
    static char temp_str[80] = "";
    strcpy(temp_str, "");
    snprintf(temp_str, sizeof(temp_str), "%4s %8s %3s", bus, module, OnOffToStr(on_off));
    if(is_contain(temp_str, key_word1, key_word2)) {
        if(on_off) {
            LOG_WARNING(CLK, "%s", temp_str);
        } else {
            LOG_NOTICE(CLK, "%s", temp_str);
        }
        res = true;
    }
    return res;
}

bool periph_clock_diag(char* key_word1, char* key_word2) {
    bool res = false;
    set_log_level(CLK, LOG_LEVEL_NOTICE);

    return res;
}

const char* Bus2Str(ClockBus_t bus_code) {
    char* name = "?";
    switch((uint8_t)bus_code) {
    case CLOCK_BUS_AHB1:
        name = "AHB1";
        break;
    case CLOCK_BUS_AHB2:
        name = "AHB2";
        break;
    case CLOCK_BUS_APB1:
        name = "APB1";
        break;
    case CLOCK_BUS_APB2:
        name = "APB2";
        break;
    }
    return name;
}

const char* At32ClockSrc2Str(crm_sclk_type crm_sclk) {
    char* name = "?";
    switch((uint8_t)crm_sclk) {
    case CRM_SCLK_HICK:
        name = "HICK";
        break;
    case CRM_SCLK_HEXT:
        name = "HEXT";
        break;
    case CRM_SCLK_PLL:
        name = "PLL";
        break;
    }
    return name;
}

const char* At32Clock2Str(crm_clocks_freq_type* const Node) {
    static char name[100] = "";
    if(Node) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%ssclk:%u,", name, Node->sclk_freq);
        snprintf(name, sizeof(name), "%sahb:%u,", name, Node->ahb_freq);
        snprintf(name, sizeof(name), "%sapb1:%u,", name, Node->apb1_freq);
        snprintf(name, sizeof(name), "%sapb2:%u", name, Node->apb2_freq);
    }
    return name;
}

bool clock_custom_diag(void) {
    bool res = false;
    crm_sclk_type crm_sclk = crm_sysclk_switch_status_get();
    LOG_INFO(SYS, "crm_sclk %u=%s", crm_sclk, At32ClockSrc2Str(crm_sclk));

    crm_clocks_freq_type clocks_struct = {0};
    crm_clocks_freq_get(&clocks_struct);
    LOG_INFO(SYS, "%s", At32Clock2Str(&clocks_struct));

    res = true;
    uint32_t instrictions = clock_int_per_us(100);
    LOG_INFO(SYS, "InstrPerUs 100Us %u 1Us-%u", instrictions, instrictions / 100);
    instrictions = clock_int_per_ms(100);
    LOG_INFO(SYS, "InstrPerMs %u", instrictions / 100);

    return res;
}
