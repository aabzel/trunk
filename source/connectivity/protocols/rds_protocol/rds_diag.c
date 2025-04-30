#include "rds_diag.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "log.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "rds_protocol.h"
#include "rds_types.h"

static const CountryCodeInfo_t CountryCodeInfo[] = {
    {
        .CountryCode = 1,
        .name = "DE",
    },
    {
        .CountryCode = 1,
        .name = "GR",
    },
    {
        .CountryCode = 1,
        .name = "MA",
    },
    {
        .CountryCode = 1,
        .name = "MD",
    },
    {
        .CountryCode = 2,
        .name = "DZ",
    },
    {
        .CountryCode = 2,
        .name = "CY",
    },
    {
        .CountryCode = 2,
        .name = "CZ",
    },
    {
        .CountryCode = 2,
        .name = "IE",
    },
    {
        .CountryCode = 2,
        .name = "EE",
    },
    {
        .CountryCode = 5,
        .name = "IT",
    },
    {
        .CountryCode = 5,
        .name = "JO",
    },
    {
        .CountryCode = 5,
        .name = "SK",
    },
    {
        .CountryCode = 6,
        .name = "UA",
    },
    {
        .CountryCode = 6,
        .name = "BE",
    },
    {
        .CountryCode = 6,
        .name = "FI",
    },
    {
        .CountryCode = 6,
        .name = "SY",
    },
    {
        .CountryCode = 7,
        .name = "Russia",
    },
    {
        .CountryCode = 7,
        .name = "LU",
    },
    {
        .CountryCode = 7,
        .name = "TN",
    },
    {
        .CountryCode = 9,
        .name = "AT",
    },
    {
        .CountryCode = 9,
        .name = "DK",
    },
    {
        .CountryCode = 9,
        .name = "LI",
    },
    {
        .CountryCode = 9,
        .name = "LV",
    },
    {
        .CountryCode = 9,
        .name = "SI",
    },
    {
        .CountryCode = 12,
        .name = "MT",
    },
    {
        .CountryCode = 12,
        .name = "GB",
    },
    {
        .CountryCode = 12,
        .name = "LT",
    },
    {
        .CountryCode = 12,
        .name = "HR",
    },
    {
        .CountryCode = 0xB,
        .name = "HU",
    },
    {
        .CountryCode = 0xB,
        .name = "IQ",
    },
    {
        .CountryCode = 0xB,
        .name = "MC",
    },
    {
        .CountryCode = 0xF,
        .name = "EG",
    },
    {
        .CountryCode = 0xF,
        .name = "FR",
    },
    {
        .CountryCode = 0xF,
        .name = "NO",
    },
    {
        .CountryCode = 0xF,
        .name = "BY",
    },
    {
        .CountryCode = 0xF,
        .name = "BA",
    },
};

const char* MessageGroup2Str(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case 0:
        name = "A";
        break;
    case 1:
        name = "B";
        break;
    }
    return name;
}

const char* CovAreaCode2Str(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case COV_AREA_CODE_L:
        name = "Local";
        break;
    case COV_AREA_CODE_I:
        name = "International";
        break;
    case COV_AREA_CODE_N:
        name = "National";
        break;
    case COV_AREA_CODE_S:
        name = "Supre-Region";
        break;
    case COV_AREA_CODE_R1:
    case COV_AREA_CODE_R2:
    case COV_AREA_CODE_R3:
    case COV_AREA_CODE_R4:
    case COV_AREA_CODE_R5:
    case COV_AREA_CODE_R6:
    case COV_AREA_CODE_R7:
    case COV_AREA_CODE_R8:
    case COV_AREA_CODE_R9:
    case COV_AREA_CODE_R10:
    case COV_AREA_CODE_R11:
    case COV_AREA_CODE_R12:
        name = "Regional";
        break;
    }
    return name;
}

const char* ProgramType2Str(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case PROG_TYPE_UNDEF:
        name = "??";
        break;
    case PROG_TYPE_NEWS:
        name = "News";
        break;
    case PROG_TYPE_CURRENT_AFFAIRS:
        name = "CurrentAffairs";
        break;
    case PROG_TYPE_INFORMATION:
        name = "Information";
        break;
    case PROG_TYPE_SPORT:
        name = "Sport";
        break;
    case PROG_TYPE_EDUCATION:
        name = "Education";
        break;
    case PROG_TYPE_DRAMA:
        name = "Drama";
        break;
    case PROG_TYPE_CULTURE:
        name = "Culture";
        break;
    case PROG_TYPE_SCIENCE:
        name = "Science";
        break;
    case PROG_TYPE_VARIED:
        name = "Varied";
        break;
    case PROG_TYPE_POP_MUSIC:
        name = "PopMusic";
        break;
    case PROG_TYPE_ROCK_MUSIC:
        name = "RockMusic";
        break;
    case PROG_TYPE_EASY_LISTENING:
        name = "EasyListening";
        break;
    case PROG_TYPE_LIGHT_CLASSICAL:
        name = "LightClassical";
        break;
    case PROG_TYPE_SERIOUS_CLASSICAL:
        name = "LightClassical";
        break;
    case PROG_TYPE_OTHER_MUSIC:
        name = "OtherMusic";
        break;
    case PROG_TYPE_WEATHER:
        name = "Weather";
        break;
    case PROG_TYPE_FINANCE:
        name = "Finance";
        break;
    case PROG_TYPE_CHILDREN_PROGRAMMES:
        name = "ChildrenProgs";
        break;
    case PROG_TYPE_SOCIAL_AFFAIRS:
        name = "SocialAffairs";
        break;
    case PROG_TYPE_RELIGION:
        name = "Religion";
        break;
    case PROG_TYPE_PHONE_IN:
        name = "PhoneIn";
        break;
    case PROG_TYPE_TRAVEL:
        name = "Travel";
        break;
    case PROG_TYPE_LEISURE:
        name = "Leisure";
        break;
    case PROG_TYPE_JAZZ_MUSIC:
        name = "JazzMusic";
        break;
    case PROG_TYPE_COUNTRY_MUSIC:
        name = "CountryMusic";
        break;
    case PROG_TYPE_NATIONAL_MUSIC:
        name = "NationalMusic";
        break;
    case PROG_TYPE_OLDIES_MUSIC:
        name = "OldiesMusic";
        break;
    case PROG_TYPE_FOLK_MUSIC:
        name = "FolkMusic";
        break;
    case PROG_TYPE_DOCUMENTARY:
        name = "Documentary";
        break;
    case PROG_TYPE_ALARM_TEST:
        name = "AlarmTest";
        break;
    case PROG_TYPE_ALARM:
        name = "Alarm";
        break;
    }
    return name;
}

char* CountryCode2Str(uint8_t code) {
    static char name[100] = "?";
    uint32_t i = 0;
    strcpy(name, "");
    for(i = 0; i < ARRAY_SIZE(CountryCodeInfo); i++) {
        if(CountryCodeInfo[i].CountryCode == code) {
            snprintf(name, sizeof(name), "%s %s", name, CountryCodeInfo[i].name);
        }
    }
    return name;
}

const char* GroupType2Str(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case GR_TYPE_BASIC:
        name = "TuningSwitching";
        break;
    case GR_TYPE_PROG_NUM:
        name = " ItemNumber";
        break;
    case GR_TYPE_RADIO_TEXT:
        name = "Text";
        break;
    case GR_TYPE_APP_ID:
        name = "AppId4OpenDatApp";
        break;
    case GR_TYPE_CLOCK_TIME_DATE:
        name = "ClkTime&Date";
        break;

    case GR_TYPE_DATA_CH:
        name = "Data";
        break;
    case GR_TYPE_IN_HOUSE_APP:
        name = "InHouseApp";
        break;
    case GR_TYPE_PADDING:
        name = "Padding";
        break;
    case GR_TYPE_TRAFFIC_MES:
        name = "TrafficMes";
        break;

    case GR_TYPE_EMERGENCY:
        name = "Emergensy";
        break;
    case GR_TYPE_PROG_TYPE_NAME:
        name = "ProgTypeName";
        break;
    case GR_TYPE_OPEN_DATA_APP:
        name = "OpenDataApp";
        break;

    case GR_TYPE_ENH_OTHER_NET_INF:
        name = "EnhOterNetInfo";
        break;
    case GR_TYPE_ENH_RADIO_PAGING:
        name = "EnhRadioPaging";
        break;
    case GR_TYPE_RBDS:
        name = "RBDS";
        break;
    }
    return name;
}


bool rds_diag(void) {
    cli_printf("RxPktCnt: %u" CRLF, RdsProtocol.rx_pkt_cnt);
    cli_printf("TimeCnt: %u" CRLF, RdsProtocol.time_cnt);
    cli_printf("TextCnt: %u" CRLF, RdsProtocol.text_cnt);
    cli_printf("RadioText: [%s]" CRLF, RdsProtocol.RadioText);
    print_mem((uint8_t*)RdsProtocol.RadioText, 64, true, true, true, true);
    cli_printf("ProgServiceName: [%s]" CRLF, RdsProtocol.ProgServiceName);
    print_mem((uint8_t*)RdsProtocol.ProgServiceName, 8, true, true, true, true);
    cli_printf("ProgTypeName: [%s]" CRLF, RdsProtocol.ProgTypeName);
    print_mem((uint8_t*)RdsProtocol.ProgTypeName, 8, true, true, true, true);
    return true;
}

bool RdsDiagNode(RdsProtocol_t* Node){
	bool res = false;
	if(Node){
	    LOG_DEBUG(RDS, "CountryCode %u %s", Node->Message.BlockA.program_id.country_code,
	              CountryCode2Str(Node->Message.BlockA.program_id.country_code));
	    LOG_DEBUG(RDS, "ProgAreaCov %u %s", Node->Message.BlockA.program_id.prog_area_coverage,
	              CovAreaCode2Str(Node->Message.BlockA.program_id.prog_area_coverage));
	    LOG_DEBUG(RDS, "ProgRefNum %u", Node->Message.BlockA.program_id.prog_ref_num);

	    LOG_DEBUG(RDS, "App %u", Node->Message.BlockB.app);
	    LOG_DEBUG(RDS, "Traffic Program %u", Node->Message.BlockB.tp);
	    LOG_DEBUG(RDS, "ProgramType %u %s", Node->Message.BlockB.pty,
	              ProgramType2Str(Node->Message.BlockB.pty));
	    LOG_DEBUG(RDS, "MessageGroup %u %s", Node->Message.BlockB.b0,
	              MessageGroup2Str(Node->Message.BlockB.b0));
	    LOG_DEBUG(RDS, "GroupType %u %s", Node->Message.BlockB.group_type,
	              GroupType2Str(Node->Message.BlockB.group_type));
	}
    return res;
}

bool rds_print_message(RdsMessage_t* RdsMessage) {
    bool res = false;
    if(RdsMessage) {
        res = false;
        cli_printf("RDS HexDump:" CRLF);
        print_mem(RdsMessage->byte, 8, true, true, true, true);

        cli_printf("%04x ", RdsMessage->BlockA.word);
        cli_printf("%04x ", RdsMessage->BlockB.word);
        cli_printf("%04x ", RdsMessage->BlockC.word);
        cli_printf("%04x " CRLF, RdsMessage->BlockD.word);
        print_mem(RdsMessage->byte, 8, true, true, true, true);

        cli_printf("RDS BinDump:" CRLF);
        cli_printf("%s ", utoa_bin16(RdsMessage->BlockA.word));
        cli_printf("%s ", utoa_bin16(RdsMessage->BlockB.word));
        cli_printf("%s ", utoa_bin16(RdsMessage->BlockC.word));
        cli_printf("%s " CRLF, utoa_bin16(RdsMessage->BlockD.word));
    }

    return res;
}

const char* ClockTimeDate2Str(const ClockTimeDate_t *const Node){
    static char text[80] = "";
    if(Node){

    snprintf(text, sizeof(text), "DayCode:%u,LocTimeOffSet:%d,Time:%u:%u",
    		Node->mod_jul_day_code, RdsLocTimeOffSet2Num(Node->loc_time_offset), Node->hour,
             Node->min);
    }
    return text;
}
